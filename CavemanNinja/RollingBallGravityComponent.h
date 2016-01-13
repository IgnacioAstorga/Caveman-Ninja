#ifndef __ROLLINGBALLGRAVITYCOMPONENT_H__
#define __ROLLINGBALLGRAVITYCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"
#include "Point.h"

class ColliderComponent;
class DieOnPlayerAttackComponent;

class RollingBallGravityComponent : public Component
{
public:
	RollingBallGravityComponent(float gravity, float friction, ColliderComponent* colliderComponent);
	virtual ~RollingBallGravityComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	float friction;
	bool falling;

	fPoint lastPosition;
	fPoint lastFrameVelocity;

	ColliderComponent* colliderComponent;
	DieOnPlayerAttackComponent* lifeComponent;
};
#endif //__ENEMYGRAVITYCOMPONENT_H__