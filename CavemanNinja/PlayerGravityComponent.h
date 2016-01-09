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
	PlayerGravityComponent(float gravity, ColliderComponent* colliderComponent, float verticalTolerance = 5.0f);
	virtual ~PlayerGravityComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	float verticalTolerance;

	bool falling;

	ColliderComponent* colliderComponent;
	PlayerJumpComponent* jumpComponent;

	unsigned int landSound;
};
#endif //__PLAYERGRAVITYCOMPONENT_H__