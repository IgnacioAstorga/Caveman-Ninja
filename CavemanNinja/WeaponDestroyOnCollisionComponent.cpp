#include "WeaponDestroyOnCollisionComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "WeaponComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"

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
	{
		entity->Destroy();	// Destruye la entidad

		// Recupera el componente de ataque del jugador
		WeaponComponent* playerWeapon = GameController->player->FindComponent<WeaponComponent>();
		if (playerWeapon == NULL)	// El arma puede cambiar, hay que recuperarlo cada vez
			return true;

		playerWeapon->projectileCount -= 1;	// Reduce en uno la cuenta de proyectiles disparados
	}
	return true;
}
