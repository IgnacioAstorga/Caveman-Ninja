#include "WeaponDestroyOnCollisionComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "WeaponComponent.h"

WeaponDestroyOnCollisionComponent::WeaponDestroyOnCollisionComponent(ColliderType colliderType, WeaponComponent* weaponComponent)
{
	this->colliderType = colliderType;
	this->weaponComponent = weaponComponent;
}

WeaponDestroyOnCollisionComponent::~WeaponDestroyOnCollisionComponent()
{
	// No hace nada
}

bool WeaponDestroyOnCollisionComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	if (other->GetType() == colliderType)
	{
		entity->Destroy();	// Destruye la entidad
		weaponComponent->projectileCount -= 1;	// Reduce en uno la cuenta de proyectiles disparados
	}
	return true;
}
