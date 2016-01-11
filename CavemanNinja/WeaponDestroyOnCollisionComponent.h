#ifndef __WEAPONDESTROYONCOLLISIONCOMPONENT_H__
#define __WEAPONDESTROYONCOLLISIONCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"

class WeaponComponent;

class WeaponDestroyOnCollisionComponent : public Component
{
public:
	WeaponDestroyOnCollisionComponent(ColliderType colliderType, WeaponComponent* weaponComponent);
	virtual ~WeaponDestroyOnCollisionComponent();

protected:
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	ColliderType colliderType;
	WeaponComponent* weaponComponent;
};
#endif // __WEAPONDESTROYONCOLLISIONCOMPONENT_H__