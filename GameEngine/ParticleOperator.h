#ifndef __PARTICLEOPERATOR_H__
#define __PARTICLEOPERATOR_H__

#include "Globals.h"

class Particle;
class ParticleSystem;

class ParticleOperator
{
public:
	ParticleOperator(bool start_enabled = true);
	virtual ~ParticleOperator();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	void SetParticleSystem(ParticleSystem* particleSystem);

	virtual update_status Modify(Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEOPERATOR_H__