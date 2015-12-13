#ifndef __COLORRANDOMINITIALIZER_H__
#define __COLORRANDOMINITIALIZER_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"
#include "Color.h"

class ColorRandomInitializer : public ParticleInitializer
{
public:
	ColorRandomInitializer(const Color& colorMin, const Color& colorMax) {
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

#endif //  __COLORRANDOMINITIALIZER_H__
