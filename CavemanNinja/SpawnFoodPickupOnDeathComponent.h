#ifndef __SPAWNFOODPICKUPONDEATHCOMPONENT_H__
#define __SPAWNFOODPICKUPONDEATHCOMPONENT_H__

#include "SpawnEntityOnDeathComponent.h"
#include "FoodPickup.h"

class SpawnFoodPickupOnDeathComponent : public SpawnEntityOnDeathComponent
{
public:
	SpawnFoodPickupOnDeathComponent(FoodPickupType type) : SpawnEntityOnDeathComponent(), type(type) {};
	~SpawnFoodPickupOnDeathComponent() {};

protected:
	Entity* GetEntity()
	{
		return new FoodPickup(type, "food_pickup_" + entity->name);
	};

public:
	FoodPickupType type;
};
#endif	// __SPAWNFOODPICKUPONDEATHCOMPONENT_H__