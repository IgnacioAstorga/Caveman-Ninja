#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include "Color.h"

class Particle
{
public:
	fPoint position = fPoint(0.0f, 0.0f);
	fPoint speed = fPoint(0.0f, 0.0f);
	fPoint originalScale = fPoint(1.0f, 1.0f);
	fPoint scale = originalScale;
	float rotation = 0.0f;
	float duration = 0.0f;
	float lifetime = 0.0f;
	Color tint = Color();
	bool dead = false;
};

#endif // __PARTICLE_H__