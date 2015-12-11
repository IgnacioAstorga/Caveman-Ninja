#include <stdlib.h>

float random() {
	return (float)rand() / (float)RAND_MAX;
}

float random(float min, float max)
{
	return min + random() * (max - min);
}

float random(float max) {
	return random(0.0f, max);
}