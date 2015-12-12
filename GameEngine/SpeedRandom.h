#ifndef __SPEEDRANDOM_H__
#define __SPEEDRANDOM_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"

class SpeedRandom : public ParticleInitializer
{
public:
	SpeedRandom(float xMin, float xMax, float yMin, float yMax) {
		this->xMin = xMin;
		this->xMax = xMax;
		this->yMin = yMin;
		this->yMax = yMax;
	}

	bool Initialize(Particle& particle)
	{
		fPoint speed;
		Random r;
		speed.x = r.Range(xMin, xMax);
		speed.y = r.Range(yMin, yMax);
		particle.speed = speed;

		return true;
	}

private:
	float xMin, xMax, yMin, yMax;
};

#endif //  __SPEEDRANDOM_H__
