#include "ParticleInitializer.h"
#include "ParticleSystem.h"

ParticleInitializer::ParticleInitializer(bool start_enabled)
	: enabled(start_enabled) {};

ParticleInitializer::~ParticleInitializer() {};

bool ParticleInitializer::IsEnabled() const
{
	return enabled;
}

bool ParticleInitializer::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
}

bool ParticleInitializer::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
}

void ParticleInitializer::SetParticleSystem(ParticleSystem* particleSystem)
{
	system = particleSystem;
}