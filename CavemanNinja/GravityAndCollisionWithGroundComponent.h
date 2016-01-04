#ifndef __GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__
#define __GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"
#include "Point.h"

class ColliderComponent;
class PlayerJumpComponent;

class GravityAndCollisionWithGroundComponent : public Component
{
public:
	GravityAndCollisionWithGroundComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float verticalTolerance = 5.0f, float step_size = 0.5f);
	virtual ~GravityAndCollisionWithGroundComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	bool falling;
	ColliderType groundColliderType;
	ColliderComponent* colliderComponent;
	PlayerJumpComponent* jumpComponent;
	float verticalTolerance;
	float step_size;
};
#endif //__GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__