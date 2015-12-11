#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "stdlib.h"

class Random
{
public:

	Random() {
		// No hace nada
	}

	float Value() {
		return (float)rand() / (float) RAND_MAX;
	}

	float Range(float min, float max) {
		return min + Value() * (max - min);
	}

	float Top(float max) {
		return Range(0, max);
	}
};
#endif // __RANDOM_H__