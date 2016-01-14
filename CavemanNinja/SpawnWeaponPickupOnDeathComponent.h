#ifndef __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__
#define __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__

#include "SpawnEntityOnDeathComponent.h"
#include "WeaponPickup.h"

class SpawnWeaponPickupOnDeathComponent : public SpawnEntityOnDeathComponent
{
public:
	SpawnWeaponPickupOnDeathComponent(WeaponPickupType type) : SpawnEntityOnDeathComponent(), type(type) {};
	~SpawnWeaponPickupOnDeathComponent() {};

protected:
	Entity * SpawnWeaponPickupOnDeathComponent::GetEntity()
	{
		return new WeaponPickup((WeaponPickupType)type, "weapon_pickup_" + entity->name);
	};

public:
	WeaponPickupType type;
};

#endif	// __SPAWNWEAPONPICKUPONDEATHCOMPONENT_H__