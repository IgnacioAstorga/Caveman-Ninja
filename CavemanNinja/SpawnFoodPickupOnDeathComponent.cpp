#include "SpawnFoodPickupOnDeathComponent.h"
#include "FoodPickup.h"

Entity * SpawnFoodPickupOnDeathComponent::GetPickup(int type)
{
	return new FoodPickup((FoodPickupType)type, "food_pickup_" + entity->name);
}
