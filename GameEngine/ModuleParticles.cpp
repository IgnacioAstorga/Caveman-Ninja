#include "ModuleParticles.h"
#include "ParticleSystem.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{
	// No hace nada en particular
}

ModuleParticles::~ModuleParticles()
{
	// No hace nada en particular
}

bool ModuleParticles::Start()
{
	LOG("Starting Particles Module");

	bool ret = true;

	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	return ret;
}

update_status ModuleParticles::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate();

	return ret;
}

update_status ModuleParticles::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Update();

	return ret;
}

update_status ModuleParticles::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate();
	
	return ret;
}

bool ModuleParticles::CleanUp()
{
	LOG("Cleaning up Particles Module");

	bool ret = true;

	// Limpia la lista de partículas
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->CleanUp();
	particleSystems.clear();

	return true;
}

void ModuleParticles::RegisterParticleSystem(ParticleSystem* particleSystem)
{
	LOG("Particle System registration");

	if (std::find(particleSystems.begin(), particleSystems.end(), particleSystem) == particleSystems.end())
	{
		particleSystems.push_back(particleSystem);
		particleSystem->Start();
	}
}

void ModuleParticles::UnregisterParticleSystem(ParticleSystem* particleSystem)
{
	LOG("Particle System unregistration");

	if (std::find(particleSystems.begin(), particleSystems.end(), particleSystem) == particleSystems.end())
	{
		particleSystems.remove(particleSystem);
		particleSystem->CleanUp();
	}
}