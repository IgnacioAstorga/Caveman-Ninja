#include "CavemanChargeAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"

#define CHARGE_SPEED 100.0f
#define CHARGE_STOP_DISTANCE 200.0f
#define ATTACK_DISTANCE_HORIZONTAL 40.0f
#define ATTACK_DISTANCE_VERTICAL 20.0f

CavemanChargeAIBehaviour::CavemanChargeAIBehaviour()
	: AIBehaviour(CHARGE) {}

CavemanChargeAIBehaviour::~CavemanChargeAIBehaviour()
{
	// No hace nada
}

void CavemanChargeAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;

	// Establece la orientación hacia el jugador
	if (entity->transform->GetGlobalPosition().x >= GameController->player->transform->GetGlobalPosition().x)
		cavemanManager->orientation = LEFT;
	else
		cavemanManager->orientation = RIGHT;

	// Corre en la dirección del jugador
	entity->transform->speed.x = cavemanManager->orientation * CHARGE_SPEED;
}

void CavemanChargeAIBehaviour::OnTick()
{
	fPoint thisPosition = entity->transform->GetGlobalPosition();
	fPoint playerPosition = GameController->player->transform->GetGlobalPosition();

	// Si se acerca suficiente al jugador, ataca
	if ((abs(thisPosition.x - playerPosition.x) <= ATTACK_DISTANCE_HORIZONTAL) &&
		(abs(thisPosition.y - playerPosition.y) <= ATTACK_DISTANCE_VERTICAL))
		manager->SetFlagValue(STATE, ATTACK);

	// Si se aleja demasiado del jugador, vuelve a buscarlo
	else if (abs(entity->transform->GetGlobalPosition().x - GameController->player->transform->GetGlobalPosition().x) >= CHARGE_STOP_DISTANCE)
		manager->SetFlagValue(STATE, SEARCH);
}

void CavemanChargeAIBehaviour::OnExit()
{
	// No hace nada
}
