#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "Globals.h"
#include "ParticleSystem.h"

class ParticleEmitter
{
public:
	ParticleEmitter(bool start_enabled = true) : enabled(start_enabled) {};
	virtual ~ParticleEmitter() {};

	bool IsEnabled() const
	{
		return enabled;
	}

	bool Enable()
	{
		if (enabled == false)
			return enabled = Start();
		return true;
	}

	bool Disable()
	{
		if (enabled == true)
			return enabled = !CleanUp();
		return true;
	}

	void SetParticleSystem(ParticleSystem* particleSystem)
	{
		system = particleSystem;
	}

public:
	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

	virtual update_status Emit() = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEEMITTER_H__