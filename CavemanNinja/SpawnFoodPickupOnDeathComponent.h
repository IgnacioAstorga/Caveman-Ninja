#ifndef __SPAWNFOODPICKUPONDEATHCOMPONENT_H__
#define __SPAWNFOODPICKUPONDEATHCOMPONENT_H__

#include "SpawnPickupOnDeathComponent.h"

class SpawnFoodPickupOnDeathComponent : public SpawnPickupOnDeathComponent
{
public:
	SpawnFoodPickupOnDeathComponent(int type) : SpawnPickupOnDeathComponent(type) {};
	~SpawnFoodPickupOnDeathComponent() {};

protected:
	Entity* GetPickup(int type);
};
#endif	// __SPAWNFOODPICKUPONDEATHCOMPONENT_H__