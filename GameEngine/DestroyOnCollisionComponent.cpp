#include "DestroyOnCollisionComponent.h"
#include "Collider.h"
#include "Entity.h"

DestroyOnCollisionComponent::DestroyOnCollisionComponent(bool start_enabled)
	: Component(start_enabled)
{
	// En principio no hace nada
}

DestroyOnCollisionComponent::~DestroyOnCollisionComponent()
{
	// En principio no hace nada
}

bool DestroyOnCollisionComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	if (self->GetType() != other->GetType())
		entity->Destroy();
	return true;
}