#ifndef __MOVEMENTBASIC_H__
#define __MOVEMENTBASIC_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTime.h"

class MovementBasic : public ParticleOperator
{
public:
	MovementBasic() {}

	update_status Modify(Particle& particle)
	{
		particle.position.x += particle.speed.x * App->time->DeltaTime();
		particle.position.y += particle.speed.y * App->time->DeltaTime();

		return UPDATE_CONTINUE;
	}
};

#endif //  __MOVEMENTBASIC_H__
