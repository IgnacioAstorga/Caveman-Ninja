#ifndef __ROTATIONMATCHINGSPEEDOPERATOR_H__
#define __ROTATIONMATCHINGSPEEDOPERATOR_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Globals.h"

class RotationMatchingSpeedOperator : public ParticleOperator
{
public:
	RotationMatchingSpeedOperator() {}

	update_status Modify(Particle& particle)
	{
		particle.rotation = (float)(atan2(particle.speed.y, particle.speed.x) * 180.0 / M_PI);

		return UPDATE_CONTINUE;
	}
};

#endif //  __ROTATIONMATCHINGSPEEDOPERATOR_H__
