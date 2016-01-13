#ifndef __DESTROYONCOLLISIONCOMPONENT_H__
#define __DESTROYONCOLLISIONCOMPONENT_H__

#include "Component.h"

class DestroyOnCollisionComponent : public Component
{
public:
	DestroyOnCollisionComponent(bool start_enabled = true);
	virtual ~DestroyOnCollisionComponent();

	bool OnCollisionEnter(Collider* self, Collider* other);
};

#endif // __DESTROYONCOLLISIONCOMPONENT_H__