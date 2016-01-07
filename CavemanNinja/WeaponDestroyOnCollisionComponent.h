#ifndef __WEAPONDESTROYONCOLLISIONCOMPONENT_H__
#define __WEAPONDESTROYONCOLLISIONCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"

class WeaponDestroyOnCollisionComponent : public Component
{
public:
	WeaponDestroyOnCollisionComponent(ColliderType colliderType);
	virtual ~WeaponDestroyOnCollisionComponent();

protected:
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	ColliderType colliderType;
};
#endif // __WEAPONDESTROYONCOLLISIONCOMPONENT_H__