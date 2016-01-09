#ifndef __ENEMYGRAVITYCOMPONENT_H__
#define __ENEMYGRAVITYCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"
#include "Point.h"

class ColliderComponent;
class DieOnPlayerAttackComponent;

class EnemyGravityComponent : public Component
{
public:
	EnemyGravityComponent(float gravity, ColliderComponent* colliderComponent, float verticalTolerance = 5.0f, float step_size = 0.5f);
	virtual ~EnemyGravityComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	bool falling;
	ColliderComponent* colliderComponent;
	DieOnPlayerAttackComponent* lifeComponent;
	float verticalTolerance;
	float step_size;
};
#endif //__ENEMYGRAVITYCOMPONENT_H__