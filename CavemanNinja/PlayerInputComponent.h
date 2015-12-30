#ifndef __PLAYERINPUTCOMPONENT_H__
#define __PLAYERINPUTCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"

class ColliderComponent;
class Collider;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(float speed, ColliderType wallColliderType, ColliderComponent* colliderComponent, float step_size = 0.5f);
	virtual ~PlayerInputComponent();

protected:
	bool OnPreUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float speed;
	ColliderType wallColliderType;
	ColliderComponent* colliderComponent;
	float step_size;
};
#endif //__PLAYERINPUTCOMPONENT_H__