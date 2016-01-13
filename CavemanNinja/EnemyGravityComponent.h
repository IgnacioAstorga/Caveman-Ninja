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
	EnemyGravityComponent(float gravity, ColliderComponent* colliderComponent);
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
};
#endif //__ENEMYGRAVITYCOMPONENT_H__