#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "Globals.h"

#include <list>

class ParticleEmitter;
class ParticleInitializer;
class ParticleOperator;
class ParticleRenderer;
class Particle;
class Transform;

using namespace std;

class ParticleSystem
{
public:
	ParticleSystem(Transform* transform, bool start_enabled = true);
	virtual ~ParticleSystem();
	
	bool IsEnabled();
	bool Enable();
	bool Disable();

protected:
	virtual void OnCreate() {};
	virtual void OnDestroy() {};
	virtual bool OnStart() { return true; };
	virtual bool OnCleanUp() { return true; };

public:
	void Add(ParticleEmitter* particleEmitter);
	void Add(ParticleInitializer* particleInitializer);
	void Add(ParticleOperator* particleOperator);
	void Add(ParticleRenderer* particleRenderer);

	bool CreateParticle(unsigned int amount);

	Transform* GetTransform();

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	bool active;

	list<ParticleEmitter*> emitters;
	list<ParticleInitializer*> initializers;
	list<ParticleOperator*> operators;
	list<ParticleRenderer*> renderers;

	list<Particle*> particles;

	Transform* transform;
};
#endif // __PARTICLESYSTEM_H__