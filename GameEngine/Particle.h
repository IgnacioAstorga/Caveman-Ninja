#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include "Color.h"

class Particle
{
public:
	fPoint position;
	fPoint speed;
	fPoint scale;
	float rotation;
	float lifetime;
	Color tint;
	bool dead = false;
};

#endif // __PARTICLE_H__