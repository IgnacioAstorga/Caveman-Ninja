#ifndef __PLAYERLIFECOMPONENT_H__
#define __PLAYERLIFECOMPONENT_H__

#include "Component.h"
#include "Point.h"
#include "Timer.h"

enum DeathType {
	DAMAGE,
	HARVEST
};

class PlayerInputComponent;
class PlayerGravityComponent;
class ColliderComponent;

class PlayerLifeComponent : public Component
{
public:
	PlayerLifeComponent(ColliderComponent* colliderComponent, int lifePoints, float graceTime, float harvestTime, float decayTime, bool harvesting = true);
	virtual ~PlayerLifeComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	void Heal(int amount);
	void TakeDamage(int amount, fPoint damagePosition);
	void Die(DeathType deathType, bool stop = true);
	void Decay();

public:
	int maxLifePoints;
	int currentLifePoints;
	bool hit;
	bool invulnerable;
	bool dead;
	bool harvesting;
	bool decaying;
	DeathType deathCause;

	float graceTime;
	float harvestTime;
	float decayTime;
	Timer graceTimer;
	Timer harvestTimer;
	Timer decayTimer;

	PlayerInputComponent* inputComponent;
	PlayerGravityComponent* gravityComponent;
	ColliderComponent* colliderComponent;

	unsigned int hitSound;
	unsigned int dieSound;
};
#endif // __PLAYERLIFECOMPONENT_H__