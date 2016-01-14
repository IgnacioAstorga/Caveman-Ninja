#include "SpawnWeaponPickupOnDeathComponent.h"
#include "WeaponPickup.h"

Entity * SpawnWeaponPickupOnDeathComponent::GetPickup(int type)
{
	return new WeaponPickup((WeaponPickupType)type, "weapon_pickup_" + entity->name);
}
