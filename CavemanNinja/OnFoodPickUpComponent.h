#ifndef __ONFOODPICKUPCOMPONENT_H__
#define __ONFOODPICKUPCOMPONENT_H__

#include "Component.h"

enum PickupType;

class OnFoodPickUpComponent : public Component
{
public:
	OnFoodPickUpComponent(PickupType type);
	virtual ~OnFoodPickUpComponent();

protected:
	bool OnStart();
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	PickupType type;

	unsigned int pickupSound;
};
#endif // __ONFOODPICKUPCOMPONENT_H__