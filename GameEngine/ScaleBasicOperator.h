#ifndef __SCALEBASICOPERATOR_H__
#define __SCALEBASICOPERATOR_H__

#include "ParticleOperator.h"
#include "Particle.h"

class ScaleBasicOperator : public ParticleOperator
{
public:
	ScaleBasicOperator(float startScale, float endScale, float startScaleTime = 0.0f, float endScaleTime = 1.0f)
	{
		this->startScale = startScale;
		this->endScale = endScale;
		this->startScaleTime = startScaleTime;
		this->endScaleTime = endScaleTime;
	}

	update_status Modify(Particle& particle)
	{
		if (particle.lifetime <= 0)
			return UPDATE_ERROR;

		float lifeDuration = particle.duration / particle.lifetime;
		if (lifeDuration <= startScaleTime)
		{
			particle.scale = particle.originalScale * startScale;
		}
		else if (lifeDuration <= endScaleTime)
		{
			float scale = startScale + ((lifeDuration - startScaleTime) / (endScaleTime - startScaleTime)) * (endScale - startScale);
			particle.scale = particle.originalScale * scale;
		}
		else
		{
			particle.scale = particle.originalScale * endScale;
		}

		return UPDATE_CONTINUE;
	}

private:
	float startScale, endScale;
	float startScaleTime, endScaleTime;
};

#endif //  __SCALEBASICOPERATOR_H__
