#ifndef __COLORRANDOM_H__
#define __COLORRANDOM_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"
#include "Color.h"

class ColorRandom : public ParticleInitializer
{
public:
	ColorRandom(const Color& colorMin, const Color& colorMax) {
		this->colorMin = colorMin;
		this->colorMax = colorMax;
	}

	bool Initialize(Particle& particle)
	{
		Random r;
		particle.tint.red = r.Range(colorMin.red, colorMax.red);
		particle.tint.green = r.Range(colorMin.green, colorMax.green);
		particle.tint.blue = r.Range(colorMin.blue, colorMax.blue);
		particle.tint.alpha = r.Range(colorMin.alpha, colorMax.alpha);

		return true;
	}

private:
	Color colorMin, colorMax;
};

#endif //  __COLORRANDOM_H__
