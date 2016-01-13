#include "ThrowerIdleAIBehaviour.h"
#include "ThrowerAIManager.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"

#define THROW_START_DISTANCE 100.0f
#define WALK_SPEED 15.0f

ThrowerIdleAIBehaviour::ThrowerIdleAIBehaviour()
	: AIBehaviour(IDLE) {}

ThrowerIdleAIBehaviour::~ThrowerIdleAIBehaviour()
{
	// No hace nada
}

void ThrowerIdleAIBehaviour::OnEnter()
{
	// No hace nada
}

void ThrowerIdleAIBehaviour::OnTick()
{
	if (GameController->player == NULL)
		return;

	ThrowerAIManager* throwerManager = (ThrowerAIManager*)manager;

	// Establece la orientación hacia el jugador
	if (entity->transform->GetGlobalPosition().x >= GameController->player->transform->GetGlobalPosition().x)
		throwerManager->orientation = LEFT;
	else
		throwerManager->orientation = RIGHT;

	// Hace caminar el personaje en la dirección adecuada
	entity->transform->speed.x = throwerManager->orientation * WALK_SPEED;

	// Si el jugador está suficientemente cerca, lanza la piedra
	if (GameController->player->transform->GetGlobalPosition().DistanceTo(entity->transform->GetGlobalPosition()) <= THROW_START_DISTANCE)
		manager->SetFlagValue(STATE, THROW_START);
}

void ThrowerIdleAIBehaviour::OnExit()
{
	// No hace nada
}
