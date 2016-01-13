#include "CavemanAttackAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "CircleColliderComponent.h"

#define ATTACK_OFFSET_HORIZONTAL 15.0f
#define ATTACK_OFFSET_VERTICAL -23.0f
#define ATTACK_DURATION 0.5f

CavemanAttackAIBehaviour::CavemanAttackAIBehaviour()
	: AIBehaviour(ATTACK) {}

CavemanAttackAIBehaviour::~CavemanAttackAIBehaviour()
{
	// No hace nada
}

void CavemanAttackAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador que indica la duración del ataque
	timer.SetTimer(ATTACK_DURATION);

	// Detiene al personaje mientras ataca
	entity->transform->speed.x = 0.0f;

	// Activa el collider de ataque y establece su offset
	if (!cavemanManager->attackComponent->IsEnabled())
	{
		cavemanManager->attackComponent->Enable();
		cavemanManager->attackComponent->SetOffset(cavemanManager->orientation * ATTACK_OFFSET_HORIZONTAL, ATTACK_OFFSET_VERTICAL);
	}
}

void CavemanAttackAIBehaviour::OnTick()
{
	// Si ha terminado de atacar, empieza a huir
	if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, START_RUN);
}

void CavemanAttackAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);

	// Desactiva el collider
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;
	cavemanManager->attackComponent->Disable();
}
