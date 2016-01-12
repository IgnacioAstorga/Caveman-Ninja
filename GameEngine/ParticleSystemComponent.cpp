#include "ParticleSystemComponent.h"
#include "ParticleSystem.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "Entity.h"

ParticleSystemComponent::ParticleSystemComponent(ParticleSystem* system, bool start_enabled)
	: Component(start_enabled)
{
	this->system = system;
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	RELEASE(system);
}

bool ParticleSystemComponent::OnStart()
{
	if (system == nullptr || entity == nullptr)
		return false;

	system->transform = entity->transform;
	App->particles->RegisterParticleSystem(system);

	return true;
}

bool ParticleSystemComponent::OnCleanUp()
{
	if (system == nullptr || entity == nullptr)
		return false;

	App->particles->UnregisterParticleSystem(system);
	system->transform = nullptr;

	return true;
}

ParticleSystem* ParticleSystemComponent::GetSystem() const
{
	return system;
}
