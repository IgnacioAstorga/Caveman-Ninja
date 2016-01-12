#include "ParticleEmitter.h"
#include "ParticleSystem.h"

ParticleEmitter::ParticleEmitter(bool start_enabled)
	: enabled(start_enabled) {};

ParticleEmitter::~ParticleEmitter() {};

bool ParticleEmitter::IsEnabled() const
{
	return enabled;
}

bool ParticleEmitter::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
}

bool ParticleEmitter::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
}

void ParticleEmitter::SetParticleSystem(ParticleSystem* particleSystem)
{
	system = particleSystem;
}