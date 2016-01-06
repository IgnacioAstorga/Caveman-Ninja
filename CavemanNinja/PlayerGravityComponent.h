#ifndef __PLAYERGRAVITYCOMPONENT_H__
#define __PLAYERGRAVITYCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"
#include "Point.h"

class ColliderComponent;
class PlayerJumpComponent;

class PlayerGravityComponent : public Component
{
public:
	PlayerGravityComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float verticalTolerance = 5.0f, float step_size = 0.5f);
	virtual ~PlayerGravityComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	ColliderType groundColliderType;
	float verticalTolerance;
	float step_size;
	bool falling;
	bool onGround;

	ColliderComponent* colliderComponent;
	PlayerJumpComponent* jumpComponent;

	unsigned int landSound;
};
#endif //__PLAYERGRAVITYCOMPONENT_H__