#ifndef __PARTICLEOPERATOR_H__
#define __PARTICLEOPERATOR_H__

#include "Globals.h"
#include "ParticleSystem.h"

class ParticleOperator
{
public:
	ParticleOperator() {};
	virtual ~ParticleOperator() {};

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
	virtual bool Start() {};
	virtual bool CleanUp() {};

	virtual update_status Modify(Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLEOPERATOR_H__