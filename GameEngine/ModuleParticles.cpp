#include "ModuleParticles.h"
#include "ParticleSystem.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{
	// No hace nada
}

ModuleParticles::~ModuleParticles()
{
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end(); ++it)
		RELEASE(*it);
	particleSystems.clear();
}

bool ModuleParticles::Start()
{
	bool ret = true;
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret; ++it)
		ret = (*it)->Start();
	return ret;
}

update_status ModuleParticles::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate();
	}
	return ret;
}

update_status ModuleParticles::Update()
{
	update_status ret = UPDATE_CONTINUE;
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled())
			ret = (*it)->Update();
	}
	return ret;
}

update_status ModuleParticles::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate();
	}
	return ret;
}

bool ModuleParticles::CleanUp()
{
	// Limpia la lista de partículas
	bool ret = true;
	for (list<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end() && ret; ++it)
		ret = (*it)->CleanUp();
	return ret;
}

void ModuleParticles::RegisterParticleSystem(ParticleSystem* particleSystem)
{
	if (find(particleSystems.begin(), particleSystems.end(), particleSystem) == particleSystems.end())
		particleSystems.push_back(particleSystem);
}

void ModuleParticles::RemoveParticleSystem(ParticleSystem* particleSystem)
{
	if (find(particleSystems.begin(), particleSystems.end(), particleSystem) != particleSystems.end())
	{
		particleSystems.remove(particleSystem);
		particleSystem->CleanUp();
		RELEASE(particleSystem);
	}
}