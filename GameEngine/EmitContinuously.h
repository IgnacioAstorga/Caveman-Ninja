#ifndef __EMITCONTINUOUSLY_H__
#define __EMITCONTINUOUSLY_H__

#include "ParticleEmitter.h"
#include "Application.h"
#include "ModuleTime.h"

class EmitContinuously : public ParticleEmitter
{
public:
	EmitContinuously(float rate) : rate(rate) {}

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

#endif //  __EMITCONTINUOUSLY_H__
