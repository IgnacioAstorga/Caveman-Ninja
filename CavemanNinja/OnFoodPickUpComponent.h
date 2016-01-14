#ifndef __ONFOODPICKUPCOMPONENT_H__
#define __ONFOODPICKUPCOMPONENT_H__

#include "Component.h"

enum FoodPickupType;

class OnFoodPickUpComponent : public Component
{
public:
	OnFoodPickUpComponent(FoodPickupType type);
	virtual ~OnFoodPickUpComponent();

protected:
	bool OnStart();
	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	FoodPickupType type;

	unsigned int pickupSound;
};
#endif // __ONFOODPICKUPCOMPONENT_H__