#include "CavemanRunStartAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "ModuleAudio.h"

#define RUN_START_DELAY 0.5f

CavemanRunStartAIBehaviour::CavemanRunStartAIBehaviour()
	: AIBehaviour(RUN_START) {}

CavemanRunStartAIBehaviour::~CavemanRunStartAIBehaviour()
{
	// No hace nada
}

void CavemanRunStartAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador que indica la duración del breve periodo antes de huir
	timer.SetTimer(RUN_START_DELAY);

	// Detiene al personaje mientras empieza a correr
	entity->transform->speed.x = 0.0f;

	// Reproduce el sonido
	App->audio->PlayFx(cavemanManager->runStartSound);
}

void CavemanRunStartAIBehaviour::OnTick()
{
	// Cuando esté listo, huye
	if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, RUN);
}

void CavemanRunStartAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
}