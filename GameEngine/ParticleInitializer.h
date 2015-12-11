#ifndef __PARTICLEINITIALIZER_H__
#define __PARTICLEINITIALIZER_H__

#include "Globals.h"
#include "ParticleSystem.h"

class Particle;

class ParticleInitializer
{
public:
	ParticleInitializer(bool start_enabled = true) : enabled(start_enabled) {};
	virtual ~ParticleInitializer() {};

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

	virtual bool Initialize(Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEINITIALIZER_H__