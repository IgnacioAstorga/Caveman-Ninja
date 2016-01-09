#ifndef __TOMAHAWKGRAVITYCOMPONENT_H__
#define __TOMAHAWKGRAVITYCOMPONENT_H__

#include "Component.h"
#include "Point.h"

class ColliderComponent;
class WeaponLifespanComponent;

class WeaponGravityComponent : public Component
{
	friend class Scene;

public:
	WeaponGravityComponent(float gravity, ColliderComponent* colliderComponent, float step_size = 0.1f);
	virtual ~WeaponGravityComponent();

protected:
	bool OnStart();
	bool OnUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	float gravity;
	bool falling;
	bool onGround;
	ColliderComponent* colliderComponent;
	WeaponLifespanComponent* lifespanComponent;
	float step_size;
};
#endif //__TOMAHAWKGRAVITYCOMPONENT_H__