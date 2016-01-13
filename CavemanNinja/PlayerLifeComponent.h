#ifndef __PLAYERLIFECOMPONENT_H__
#define __PLAYERLIFECOMPONENT_H__

#include "Component.h"
#include "Point.h"
#include "Timer.h"

enum DeathType {
	DAMAGE,
	HARVEST,
	EXHAUST
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
	void Hurt(int amount, DeathType type, bool stop = false);
	void Exhaust();
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
	bool exhausted;
	DeathType deathCause;

	float graceTime;
	float harvestTime;
	float decayTime;
	Timer hitTimer;
	Timer exhaustedTimer;
	Timer graceTimer;
	Timer harvestTimer;
	Timer decayTimer;

	PlayerInputComponent* inputComponent;
	PlayerGravityComponent* gravityComponent;
	ColliderComponent* colliderComponent;

	unsigned int hitSound;
	unsigned int dieSound;
	unsigned int exhaustSound;
};
#endif // __PLAYERLIFECOMPONENT_H__