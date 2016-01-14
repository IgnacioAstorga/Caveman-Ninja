#include "BoomerangAIComponent.h"
#include "Entity.h"
#include "EnemyGravityComponent.h"
#include "DieOnPlayerAttackComponent.h"
#include "EntityLifetimeComponent.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleTime.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "WeaponComponent.h"

#define DISTANCE_TOLERANCE 10.0f
#define PLAYER_VERTICAL_OFFSET -31.0f

BoomerangAIComponent::BoomerangAIComponent(float returnTime)
{
	this->returnTime = returnTime;
}

BoomerangAIComponent::~BoomerangAIComponent()
{
	// En principio no hace nada
}

bool BoomerangAIComponent::OnStart()
{
	// Establece los flags
	returning = false;
	speed = entity->transform->GetGlobalSpeed().Norm();

	// Registra e inicia el timer
	App->time->RegisterTimer(&timer);
	timer.SetTimer(returnTime);

	return true;
}

bool BoomerangAIComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);

	return true;
}

bool BoomerangAIComponent::OnUpdate()
{
	if (!returning && timer.IsTimerExpired())
		returning = true;

	fPoint playerPosition = GameController->player->transform->GetGlobalPosition();
	playerPosition.y += PLAYER_VERTICAL_OFFSET;

	// Comprueba si ha llegado a su destino
	if (returning)
	{
		if (entity->transform->GetGlobalPosition().DistanceTo(playerPosition) <= DISTANCE_TOLERANCE)
		{
			entity->Destroy();

			// Recupera el componente de ataque del jugador
			WeaponComponent* playerWeapon = GameController->player->FindComponent<WeaponComponent>();
			if (playerWeapon == NULL)	// El arma puede cambiar, hay que recuperarlo cada vez
				return true;

			playerWeapon->DecreaseCount(1);	// Reduce en uno la cuenta de proyectiles disparados

			return true;
		}
		else
			// Modifica su velocidad
			entity->transform->speed = (playerPosition - entity->transform->GetGlobalPosition()).Normalize() * speed;
	}

	return true;
}
