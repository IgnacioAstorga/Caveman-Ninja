#ifndef __ALPHAFADEINOUT_H__
#define __ALPHAFADEINOUT_H__

#include "ParticleOperator.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTime.h"

class AlphaFadeInOut : public ParticleOperator
{
public:
	AlphaFadeInOut(float endFadeIn, float startFadeOut)
		: AlphaFadeInOut(0.0f, endFadeIn, startFadeOut, 1.0f) {}

	AlphaFadeInOut(float startFadeIn, float endFadeIn, float startFadeOut, float endFadeOut)
		: AlphaFadeInOut(startFadeIn, endFadeIn, startFadeOut, endFadeOut, 0.0f, 1.0f, 0.0f) {}

	AlphaFadeInOut(float startFadeIn, float endFadeIn, float startFadeOut, float endFadeOut, float startAlpha, float middleAlpha, float endAlpha)
	{
		this->startFadeIn = startFadeIn;
		this->endFadeIn = endFadeIn;
		this->startFadeOut = startFadeOut;
		this->endFadeOut = endFadeOut;

		this->startAlpha = startAlpha;
		this->middleAlpha = middleAlpha;
		this->endAlpha = endAlpha;
	}

	update_status Modify(Particle& particle)
	{
		if (particle.lifetime <= 0)
			return UPDATE_ERROR;

		float lifeDuration = particle.duration / particle.lifetime;
		if (lifeDuration <= startFadeIn)
		{
			particle.tint.alpha = startAlpha;
		}
		else if (lifeDuration <= endFadeIn)
		{
			particle.tint.alpha = startAlpha + ((lifeDuration - startFadeIn) / (endFadeIn - startFadeIn)) * (middleAlpha - startAlpha);
		}
		else if (lifeDuration <= startFadeOut)
		{
			particle.tint.alpha = middleAlpha;
		}
		else if (lifeDuration <= endFadeOut)
		{
			particle.tint.alpha = middleAlpha + ((lifeDuration - startFadeOut) / (endFadeOut - startFadeOut)) * (endAlpha - middleAlpha);
		}
		else
		{
			particle.tint.alpha = endAlpha;
		}

		return UPDATE_CONTINUE;
	}

private:
	float startFadeIn, endFadeIn, startFadeOut, endFadeOut;
	float startAlpha, middleAlpha, endAlpha;
};

#endif //  __ALPHAFADEINOUT_H__
