#ifndef __DIEONPLAYERATTACKCOMPONENT_H__
#define __DIEONPLAYERATTACKCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

#include <string>

class ColliderComponent;
class AIComponent;
class Transform;

using namespace std;

class DieOnPlayerAttackComponent : public Component
{
public:
	DieOnPlayerAttackComponent(float decayTime, fPoint flySpeed, string dieSoundName, ColliderComponent* colliderComponent, bool start_enabled = true);
	~DieOnPlayerAttackComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	void Die(Transform* otherTransform, bool big = false);
	void Decay();

public:
	float decayTime;
	fPoint flySpeed;
	string dieSoundName;

	bool dead;
	bool decaying;

	Timer decayTimer;

	ColliderComponent* colliderComponent;
	AIComponent* aiComponent;

	unsigned int hitSound;
	unsigned int dieSound;
};
#endif	// __DIEONPLAYERATTACKCOMPONENT_H__