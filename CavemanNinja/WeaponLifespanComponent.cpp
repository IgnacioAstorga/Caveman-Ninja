#include "WeaponLifespanComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "WeaponComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"

WeaponLifespanComponent::WeaponLifespanComponent(float lifeTime)
{
	this->lifeTime = lifeTime;
}

WeaponLifespanComponent::~WeaponLifespanComponent()
{
	// No hace nada
}

bool WeaponLifespanComponent::OnStart()
{
	// Registra el timer y lo inicia
	App->time->RegisterTimer(&lifetimeTimer);
	lifetimeTimer.SetTimer(lifeTime);

	return true;
}

bool WeaponLifespanComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&lifetimeTimer);

	return true;
}

bool WeaponLifespanComponent::OnPostUpdate()
{
	if (lifetimeTimer.IsTimerExpired())
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

void WeaponLifespanComponent::Reset()
{
	Reset(lifeTime);
}

void WeaponLifespanComponent::Reset(float lifeTime)
{
	lifetimeTimer.SetTimer(lifeTime);
}
