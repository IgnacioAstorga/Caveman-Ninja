#ifndef __DIEONPLAYERATTACKCOMPONENT_H__
#define __DIEONPLAYERATTACKCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class ColliderComponent;
class AIComponent;

class DieOnPlayerAttackComponent : public Component
{
public:
	DieOnPlayerAttackComponent(float decayTime, ColliderComponent* colliderComponent, bool start_enabled = true);
	~DieOnPlayerAttackComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	void Decay();

public:
	float decayTime;
	bool dead;
	bool decaying;

	Timer decayTimer;

	ColliderComponent* colliderComponent;
	AIComponent* aiComponent;

	unsigned int hitSound;
	unsigned int dieSound;
};
#endif	// __DIEONPLAYERATTACKCOMPONENT_H__