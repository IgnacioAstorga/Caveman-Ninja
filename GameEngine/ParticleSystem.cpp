#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "ParticleInitializer.h"
#include "ParticleOperator.h"
#include "ParticleRenderer.h"
#include "Particle.h"

ParticleSystem::ParticleSystem()
{
	// Llamada al método de usuario
	OnCreate();
}

ParticleSystem::~ParticleSystem()
{
	// Llamada al método de usuario
	OnDestroy();

	// Destruye todos los elementos
	for (list<ParticleEmitter*>::iterator it = emitters.begin(); it != emitters.end(); ++it)
		RELEASE(*it);
	emitters.clear();
	for (list<ParticleInitializer*>::iterator it = initializers.begin(); it != initializers.end(); ++it)
		RELEASE(*it);
	initializers.clear();
	for (list<ParticleOperator*>::iterator it = operators.begin(); it != operators.end(); ++it)
		RELEASE(*it);
	operators.clear();
	for (list<ParticleRenderer*>::iterator it = renderers.begin(); it != renderers.end(); ++it)
		RELEASE(*it);
	renderers.clear();

	// Destruye las partículas (no es realmente necesario)
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		RELEASE(*it);
	particles.clear();
}

bool ParticleSystem::IsEnabled()
{
	return active;
}

bool ParticleSystem::Enable()
{
	if (active == false)
		return active = Start();
	return true;
}

bool ParticleSystem::Disable()
{
	if (active == true)
		return active = !CleanUp();
	return true;
}

void ParticleSystem::Add(ParticleEmitter* particleEmitter)
{
	emitters.push_back(particleEmitter);
	particleEmitter->SetParticleSystem(this);
}

void ParticleSystem::Add(ParticleInitializer* particleInitializer)
{
	initializers.push_back(particleInitializer);
	particleInitializer->SetParticleSystem(this);
}

void ParticleSystem::Add(ParticleOperator* particleOperator)
{
	operators.push_back(particleOperator);
	particleOperator->SetParticleSystem(this);
}

void ParticleSystem::Add(ParticleRenderer* particleRenderer)
{
	renderers.push_back(particleRenderer);
	particleRenderer->SetParticleSystem(this);
}

bool ParticleSystem::CreateParticle(unsigned int amount)
{
	for (unsigned int i = 0; i < amount; ++i) {
		// Crea una partícula nueva y la registra
		Particle* particle = new Particle();
		particles.push_back(particle);

		// Inicializa la partícula
		bool ret = true;
		for (list<ParticleInitializer*>::iterator it = initializers.begin(); it != initializers.end() && ret; ++it)
			ret = (*it)->Initialize(*particle);

		return ret;
	}
}

bool ParticleSystem::Start()
{
	bool ret = true;

	// Inicializa todos los elementos
	for (list<ParticleEmitter*>::iterator it = emitters.begin(); it != emitters.end() && ret; ++it)
		ret = (*it)->Start();
	for (list<ParticleInitializer*>::iterator it = initializers.begin(); it != initializers.end() && ret; ++it)
		ret = (*it)->Start();
	for (list<ParticleOperator*>::iterator it = operators.begin(); it != operators.end() && ret; ++it)
		ret = (*it)->Start();
	for (list<ParticleRenderer*>::iterator it = renderers.begin(); it != renderers.end() && ret; ++it)
		ret = (*it)->Start();

	return ret;
}

update_status ParticleSystem::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	// En PreUpdate, llama a los emisores
	for (list<ParticleEmitter*>::iterator it = emitters.begin(); it != emitters.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Emit();

	return ret;
}

update_status ParticleSystem::Update()
{
	update_status ret = UPDATE_CONTINUE;

	// En Update, llama a los operadores para cada partícula
	for (list<Particle*>::iterator particle = particles.begin(); particle != particles.end(); ++particle)
		for (list<ParticleOperator*>::iterator it = operators.begin(); it != operators.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled())
				ret = (*it)->Modify(*(*particle));

	return ret;
}

update_status ParticleSystem::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	// Antes de nada, borra las partículas muertas
	for (list<Particle*>::iterator particle = particles.begin(); particle != particles.end(); ++particle)
		if ((*particle)->dead)
		{
			particle = particles.erase(particle);	// Eliminación segura de la lista mientras se recorre
			RELEASE(*particle);
		}
	

	// En PostUpdate, llama a los renderizadores para cada partícula
	for (list<Particle*>::iterator particle = particles.begin(); particle != particles.end(); ++particle)
		for (list<ParticleRenderer*>::iterator it = renderers.begin(); it != renderers.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled())
				ret = (*it)->Render(*(*particle));

	return ret;
}

bool ParticleSystem::CleanUp()
{
	bool ret = true;

	// Limpia todos los elementos
	for (list<ParticleEmitter*>::iterator it = emitters.begin(); it != emitters.end() && ret; ++it)
		ret = (*it)->CleanUp();
	for (list<ParticleInitializer*>::iterator it = initializers.begin(); it != initializers.end() && ret; ++it)
		ret = (*it)->CleanUp();
	for (list<ParticleOperator*>::iterator it = operators.begin(); it != operators.end() && ret; ++it)
		ret = (*it)->CleanUp();
	for (list<ParticleRenderer*>::iterator it = renderers.begin(); it != renderers.end() && ret; ++it)
		ret = (*it)->CleanUp();

	// Elimina las partículas guardadas
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end() && ret; ++it)
		RELEASE(*it);
	particles.clear();

	return ret;
}