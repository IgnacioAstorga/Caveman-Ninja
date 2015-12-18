#ifndef __DESTROYONCOLLISIONCOMPONENT_H__
#define __DESTROYONCOLLISIONCOMPONENT_H__

#include "Component.h"
#include "Collider.h"
#include "Entity.h"

class DestroyOnCollisionComponent : public Component
{
public:
	DestroyOnCollisionComponent(bool start_enabled = true) : Component(start_enabled)
	{
		// En principio no hace nada
	}

	~DestroyOnCollisionComponent()
	{
		// En principio no hace nada
	}

	bool OnCollisionExit(Collider* self, Collider* other)
	{
		entity->Destroy();
		return true;
	}
};

#endif // __DESTROYONCOLLISIONCOMPONENT_H__