#include "SpawnPickupOnDeathComponent.h"
#include "Pickup.h"
#include "Transform.h"

SpawnPickupOnDeathComponent::SpawnPickupOnDeathComponent(PickupType type)
{
	this->type = type;
}

SpawnPickupOnDeathComponent::~SpawnPickupOnDeathComponent()
{
	// En principio no hace nada
}

void SpawnPickupOnDeathComponent::Spawn()
{
	// Crea el pickup
	fPoint position = entity->transform->GetGlobalPosition();
	Pickup* pickup = new Pickup(type, "pickup_" + entity->name, position.x, position.y);
	pickup->Instantiate();
}
