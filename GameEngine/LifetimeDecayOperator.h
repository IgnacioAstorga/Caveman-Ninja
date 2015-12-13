#ifndef __LIFETIMEDECAYOPERATOR_H__
#define __LIFETIMEDECAYOPERATOR_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTime.h"

class LifetimeDecayOperator : public ParticleOperator
{
public:
	LifetimeDecayOperator() {}

	update_status Modify(Particle& particle)
	{
		particle.duration += App->time->DeltaTime();
		if (particle.duration >= particle.lifetime)
			particle.dead = true;

		return UPDATE_CONTINUE;
	}
};

#endif //  __LIFETIMEDECAYOPERATOR_H__
