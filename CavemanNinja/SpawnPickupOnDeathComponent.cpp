#include "SpawnPickupOnDeathComponent.h"
#include "Entity.h"
#include "Transform.h"

SpawnPickupOnDeathComponent::SpawnPickupOnDeathComponent(int type)
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
	Entity* pickup = GetPickup(type);
	fPoint position = entity->transform->GetGlobalPosition();
	pickup->transform->SetGlobalPosition(position.x, position.y);
	pickup->Instantiate();
}
