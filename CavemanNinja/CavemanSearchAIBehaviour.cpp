#include "CavemanSearchAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"

#define TIME_SEARCHING 1.5f
#define CHARGE_START_DISTANCE 100.0f

CavemanSearchAIBehaviour::CavemanSearchAIBehaviour()
	: AIBehaviour(SEARCH) {}

CavemanSearchAIBehaviour::~CavemanSearchAIBehaviour()
{
	// No hace nada
}

void CavemanSearchAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador para dejar de buscar
	timer.SetTimer(TIME_SEARCHING);

	// Detiene al personaje mientras busca
	entity->transform->speed.x = 0.0f;
}

void CavemanSearchAIBehaviour::OnTick()
{
	if (GameController->player == NULL)
		return;

	// Si encuentra al jugador, carga hacia él
	if (abs(entity->transform->GetGlobalPosition().x - GameController->player->transform->GetGlobalPosition().x) <= CHARGE_START_DISTANCE)
		manager->SetFlagValue(STATE, CHARGE);

	// Al terminar, si no encontró al jugador, vuelve a caminar hacia él
	else if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, IDLE);
}

void CavemanSearchAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
}
