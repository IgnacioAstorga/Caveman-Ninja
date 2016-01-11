#include "CavemanIdleAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "Random.h"

#define WAIT_FOR_SEARCH_MIN 3.0f
#define WAIT_FOR_SEARCH_MAX 5.0f
#define WALK_SPEED 25.0f

CavemanIdleAIBehaviour::CavemanIdleAIBehaviour()
	: AIBehaviour(IDLE) {}

CavemanIdleAIBehaviour::~CavemanIdleAIBehaviour()
{
	// No hace nada
}

void CavemanIdleAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*) manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador para buscar
	timer.SetTimer(Random().Range(WAIT_FOR_SEARCH_MIN, WAIT_FOR_SEARCH_MAX));

	// Establece la orientación hacia el jugador
	if (entity->transform->GetGlobalPosition().x >= GameController->player->transform->GetGlobalPosition().x)
		cavemanManager->orientation = LEFT;
	else
		cavemanManager->orientation = RIGHT;

	// Hace caminar el personaje en la dirección adecuada
	entity->transform->speed.x = cavemanManager->orientation * WALK_SPEED;
}

void CavemanIdleAIBehaviour::OnTick()
{
	// Una vez cada cierto tiempo, se detiene para buscar al jugador
	if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, SEARCH);
}

void CavemanIdleAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
}
