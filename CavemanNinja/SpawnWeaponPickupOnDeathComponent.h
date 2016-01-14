#ifndef __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__
#define __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__

#include "SpawnPickupOnDeathComponent.h"

class SpawnWeaponPickupOnDeathComponent : public SpawnPickupOnDeathComponent
{
public:
	SpawnWeaponPickupOnDeathComponent(int type) : SpawnPickupOnDeathComponent(type) {};
	~SpawnWeaponPickupOnDeathComponent() {};

protected:
	Entity* GetPickup(int type);
};
#endif	// __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__