#ifndef __ROTATIONMATCHINGSPEED_H__
#define __ROTATIONMATCHINGSPEED_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Globals.h"

class RotationMatchingSpeed : public ParticleOperator
{
public:
	RotationMatchingSpeed() {}

	update_status Modify(Particle& particle)
	{
		particle.rotation = (float)(atan2(particle.speed.y, particle.speed.y) * 180.0 / M_PI);

		return UPDATE_CONTINUE;
	}
};

#endif //  __ROTATIONMATCHINGSPEED_H__
