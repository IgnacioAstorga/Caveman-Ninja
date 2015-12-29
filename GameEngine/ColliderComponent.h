#ifndef __COLLIDERCOMPONENT_H__
#define __COLLIDERCOMPONENT_H__

#include "Component.h"

class Collider;

class ColliderComponent : public Component
{
public:
	ColliderComponent(bool start_enabled = true) : Component(start_enabled) {};
	virtual ~ColliderComponent() {};

public:
	virtual Collider* GetCollider() = 0;
};

#endif // __COLLIDERCOMPONENT_H__