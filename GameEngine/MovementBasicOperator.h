#ifndef __MOVEMENTBASICOPERATOR_H__
#define __MOVEMENTBASICOPERATOR_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ParticleSystem.h"
#include "Transform.h"

class MovementBasicOperator : public ParticleOperator
{
public:
	MovementBasicOperator() {}

	update_status Modify(Particle& particle)
	{
		particle.position.x += particle.speed.x * App->time->DeltaTime();
		particle.position.y += particle.speed.y * App->time->DeltaTime();

		return UPDATE_CONTINUE;
	}
};

#endif //  __MOVEMENTBASICOPERATOR_H__
