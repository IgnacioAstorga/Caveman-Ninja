#ifndef __PARTICLEINITIALIZER_H__
#define __PARTICLEINITIALIZER_H__

#include "Globals.h"

class Particle;
class ParticleSystem;

class ParticleInitializer
{
public:
	ParticleInitializer(bool start_enabled = true);
	virtual ~ParticleInitializer();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	void SetParticleSystem(ParticleSystem* particleSystem);

	virtual bool Initialize(Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEINITIALIZER_H__