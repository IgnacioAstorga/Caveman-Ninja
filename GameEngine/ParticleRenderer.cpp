#include "ParticleRenderer.h"
#include "ParticleSystem.h"

ParticleRenderer::ParticleRenderer(bool start_enabled)
	: enabled(start_enabled) {};

ParticleRenderer::~ParticleRenderer() {};

bool ParticleRenderer::IsEnabled() const
{
	return enabled;
}

bool ParticleRenderer::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
}

bool ParticleRenderer::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
}

void ParticleRenderer::SetParticleSystem(ParticleSystem* particleSystem)
{
	system = particleSystem;
}