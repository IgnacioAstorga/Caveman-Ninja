#include "ParticleOperator.h"
#include "ParticleSystem.h"

ParticleOperator::ParticleOperator(bool start_enabled)
	: enabled(start_enabled) {};

ParticleOperator::~ParticleOperator() {};

bool ParticleOperator::IsEnabled() const
{
	return enabled;
}

bool ParticleOperator::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
}

bool ParticleOperator::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
}

void ParticleOperator::SetParticleSystem(ParticleSystem* particleSystem)
{
	system = particleSystem;
}