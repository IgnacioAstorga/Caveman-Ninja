#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "Globals.h"

class ParticleSystem;

class ParticleEmitter
{
public:
	ParticleEmitter(bool start_enabled = true);
	virtual ~ParticleEmitter();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	void SetParticleSystem(ParticleSystem* particleSystem);

	virtual update_status Emit() = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEEMITTER_H__