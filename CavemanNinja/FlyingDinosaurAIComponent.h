#ifndef __FLYINGDINOSAURAICOMPONENT_H__
#define __FLYINGDINOSAURAICOMPONENT_H__

#include "Component.h"

class EnemyGravityComponent;
class EntityLifetimeComponent;
class DieOnPlayerAttackComponent;

class FlyingDinosaurAIComponent : public Component
{
public:
	FlyingDinosaurAIComponent(float horizontalSpeed, float acceleration, int numberOfPasses);
	virtual ~FlyingDinosaurAIComponent();

protected:
	bool OnStart();
	bool OnUpdate();

public:
	float horizontalSpeed;
	float acceleration;
	int numberOfPasses;

	int passCount;
	bool movingRight;
	fPoint targetPosition;

	EnemyGravityComponent* gravityComponent;
	EntityLifetimeComponent* lifetimeComponent;
	DieOnPlayerAttackComponent* lifeComponent;
};
#endif // __FLYINGDINOSAURAICOMPONENT_H__