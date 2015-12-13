#ifndef __LIFETIMERANDOMINITIALIZER_H__
#define __LIFETIMERANDOMINITIALIZER_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"

class LifetimeRandomInitializer : public ParticleInitializer
{
public:
	LifetimeRandomInitializer(float lifetimeMin, float lifetimeMax) {
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

#endif //  __LIFETIMERANDOMINITIALIZER_H__
