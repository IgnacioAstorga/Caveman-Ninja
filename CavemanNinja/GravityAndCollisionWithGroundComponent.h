#ifndef __GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__
#define __GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"
#include "Point.h"

class ColliderComponent;
class PlayerJumpComponent;

class GravityAndCollisionWithGroundComponent : public Component
{
	friend class Scene;

public:
	GravityAndCollisionWithGroundComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float step_size = 2.0f);
	virtual ~GravityAndCollisionWithGroundComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	float gravity;
	ColliderType groundColliderType;
	ColliderComponent* colliderComponent;
	PlayerJumpComponent* jumpComponent;
	float step_size;
	bool falling;
};
#endif //__GRAVITYANDCOLLISIONWITHGROUNDCOMPONENT_H__