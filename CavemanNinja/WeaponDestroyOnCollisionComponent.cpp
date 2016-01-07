#include "WeaponDestroyOnCollisionComponent.h"
#include "Collider.h"
#include "Entity.h"

WeaponDestroyOnCollisionComponent::WeaponDestroyOnCollisionComponent(ColliderType colliderType)
{
	this->colliderType = colliderType;
}

WeaponDestroyOnCollisionComponent::~WeaponDestroyOnCollisionComponent()
{
	// No hace nada
}

bool WeaponDestroyOnCollisionComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	if (other->GetType() == colliderType)
		entity->Destroy();
	return true;
}
