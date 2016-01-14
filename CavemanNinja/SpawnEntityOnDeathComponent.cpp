#include "SpawnEntityOnDeathComponent.h"
#include "Entity.h"
#include "Transform.h"

SpawnEntityOnDeathComponent::SpawnEntityOnDeathComponent()
{
	// En principio no hace nada
}

SpawnEntityOnDeathComponent::~SpawnEntityOnDeathComponent()
{
	// En principio no hace nada
}

void SpawnEntityOnDeathComponent::Spawn()
{
	// Crea el pickup
	Entity* pickup = GetEntity();
	fPoint position = entity->transform->GetGlobalPosition();
	pickup->transform->SetGlobalPosition(position.x, position.y);
	pickup->Instantiate();
}
