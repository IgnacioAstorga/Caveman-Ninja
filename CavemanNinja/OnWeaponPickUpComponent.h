#ifndef __ONWEAPONPICKUPCOMPONENT_H__
#define __ONWEAPONPICKUPCOMPONENT_H__

#include "Component.h"

enum WeaponPickupType;

class OnWeaponPickUpComponent : public Component
{
public:
	OnWeaponPickUpComponent(WeaponPickupType type);
	virtual ~OnWeaponPickUpComponent();

protected:
	bool OnStart();
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	WeaponPickupType type;

	unsigned int pickupSound;
};
#endif // __ONWEAPONPICKUPCOMPONENT_H__