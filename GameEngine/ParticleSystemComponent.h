#ifndef __PARTICLESYSTEMCOMPONENT_H__
#define __PARTICLESYSTEMCOMPONENT_H__

#include "Component.h"
#include "ParticleSystem.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "Entity.h"

#include "SDL.h"

class ParticleSystemComponent : public Component
{
public:
	ParticleSystemComponent(ParticleSystem* system, bool start_enabled = true) : Component(start_enabled)
	{
		this->system = system;
	}

	~ParticleSystemComponent()
	{
		RELEASE(system);
	}

	bool OnStart()
	{
		if (system == nullptr || entity == nullptr)
			return false;

		system->transform = entity->transform;
		App->particles->RegisterParticleSystem(system);

		return true;
	}

	bool OnCleanUp()
	{
		if (system == nullptr || entity == nullptr)
			return false;

		App->particles->UnregisterParticleSystem(system);
		system->transform = nullptr;

		return true;
	}

private:
	ParticleSystem* system;
};

#endif //  __PARTICLESYSTEMCOMPONENT_H__