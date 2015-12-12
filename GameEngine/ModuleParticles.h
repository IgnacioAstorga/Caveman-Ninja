#ifndef __MODULEPARTICLE_H__
#define __MODULEPARTICLE_H__

#include "Module.h"

#include <list>

class ParticleSystem;

using namespace std;

class ModuleParticles : public Module
{
public:
	ModuleParticles(bool start_enabled = true);
	~ModuleParticles();

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	void RegisterParticleSystem(ParticleSystem* particleSystem);
	void UnregisterParticleSystem(ParticleSystem* particleSystem);

private:
	list<ParticleSystem*> particleSystems;
};
#endif // __MODULEPARTICLE_H__
