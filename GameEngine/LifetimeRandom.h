#ifndef __LIFETIMERANDOM_H__
#define __LIFETIMERANDOM_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"

class LifetimeRandom : public ParticleInitializer
{
public:
	LifetimeRandom(float lifetimeMin, float lifetimeMax) {
		this->lifetimeMin = lifetimeMin;
		this->lifetimeMax = lifetimeMax;
	}

	bool Initialize(Particle& particle)
	{
		Random r;
		particle.lifetime = r.Range(lifetimeMin, lifetimeMax);
		particle.duration = 0;

		return true;
	}

private:
	float lifetimeMin, lifetimeMax;
};

#endif //  __RANDOMSPEED_H__
