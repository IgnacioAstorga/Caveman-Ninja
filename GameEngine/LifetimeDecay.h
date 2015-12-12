#ifndef __LIFETIMEDECAY_H__
#define __LIFETIMEDECAY_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTime.h"

class LifetimeDecay : public ParticleOperator
{
public:
	LifetimeDecay() {}

	update_status Modify(Particle& particle)
	{
		particle.lifetime -= App->time->DeltaTime();
		if (particle.lifetime <= 0)
			particle.dead = true;

		return UPDATE_CONTINUE;
	}
};

#endif //  __LIFETIMEDECAY_H__