#ifndef __DIEONPLAYERATTACKCOMPONENT_H__
#define __DIEONPLAYERATTACKCOMPONENT_H__

#include "Component.h"

class ColliderComponent;
class AICavemanComponent;

class DieOnPlayerAttackComponent : public Component
{
public:
	DieOnPlayerAttackComponent(float decayTime, ColliderComponent* colliderComponent, bool start_enabled = true);
	~DieOnPlayerAttackComponent();

protected:
	bool OnStart();
	bool OnUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	void Decay();

public:
	float decayTime;
	float decayDuration;
	bool dead;
	bool decaying;

	ColliderComponent* colliderComponent;
	AICavemanComponent* AIComponent;

	unsigned int hitSound;
	unsigned int dieSound;
};
#endif	// __DIEONPLAYERATTACKCOMPONENT_H__