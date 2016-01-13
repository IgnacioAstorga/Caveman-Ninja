#ifndef __PARTICLESYSTEMCOMPONENT_H__
#define __PARTICLESYSTEMCOMPONENT_H__

#include "Component.h"

class ParticleSystem;

class ParticleSystemComponent : public Component
{
public:
	ParticleSystemComponent(ParticleSystem* system, bool start_enabled = true);
	virtual ~ParticleSystemComponent();

	bool OnStart();
	bool OnCleanUp();

public:
	ParticleSystem* GetSystem() const;

private:
	ParticleSystem* system;
};

#endif //  __PARTICLESYSTEMCOMPONENT_H__