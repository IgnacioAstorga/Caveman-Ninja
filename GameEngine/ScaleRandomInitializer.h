#ifndef __SCALERANDOMINITIALIZER_H__
#define __SCALERANDOMINITIALIZER_H__

#include "ParticleInitializer.h"
#include "Particle.h"
#include "Random.h"

class ScaleRandomInitializer : public ParticleInitializer
{
public:
	ScaleRandomInitializer(float startScale, float endScale) {
		this->startScale = startScale;
		this->endScale = endScale;
	}

	bool Initialize(Particle& particle)
	{
		float scale = Random().Range(startScale, endScale);
		particle.originalScale = fPoint(scale, scale);
		particle.scale = particle.originalScale;

		return true;
	}

private:
	float startScale, endScale;
};

#endif //  __SCALERANDOMINITIALIZER_H__
