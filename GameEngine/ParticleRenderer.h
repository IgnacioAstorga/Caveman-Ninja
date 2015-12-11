#ifndef __PARTICLERENDERER_H__
#define __PARTICLERENDERER_H__

#include "Globals.h"
#include "ParticleSystem.h"

class ParticleRenderer
{
public:
	ParticleRenderer() {};
	virtual ~ParticleRenderer() {};

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

	virtual update_status Render(const Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLERENDERER_H__