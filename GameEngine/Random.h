#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "stdlib.h"

class Random
{
public:
	
	float Value() const
	{
		return (float)rand() / (float) RAND_MAX;
	}

	float Range(float min, float max) const
	{
		return min + Value() * (max - min);
	}

	float Top(float max) const
	{
		return Range(0, max);
	}
};
#endif // __RANDOM_H__