#ifndef __PARTICLERENDERER_H__
#define __PARTICLERENDERER_H__

#include "Globals.h"

class Particle;
class ParticleSystem;

class ParticleRenderer
{
public:
	ParticleRenderer(bool start_enabled = true);
	virtual ~ParticleRenderer();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	void SetParticleSystem(ParticleSystem* particleSystem);

	virtual update_status Render(const Particle& particle) = 0;

protected:
	bool enabled;
	ParticleSystem* system;
};

#endif // __PARTICLERENDERER_H__