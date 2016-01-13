#ifndef __EMITCONTINUOUSLYEMITTER_H__
#define __EMITCONTINUOUSLYEMITTER_H__

#include "ParticleEmitter.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ParticleSystem.h"

class EmitContinuouslyEmitter : public ParticleEmitter
{
public:
	EmitContinuouslyEmitter(float rate) : rate(rate) {}

	bool Start() {
		timeAlive = 0.0f;
		particleCount = 0;

		return true;
	}

	update_status Emit()
	{
		timeAlive += App->time->DeltaTime();
		unsigned int numToEmit = (int) floor(timeAlive * rate - particleCount);
		system->CreateParticle(numToEmit);
		particleCount += numToEmit;

		return UPDATE_CONTINUE;
	}

private:
	float rate;
	float timeAlive;
	unsigned int particleCount;
};

#endif //  __EMITCONTINUOUSLYEMITTER_H__
