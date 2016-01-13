#include "ThrowerRunStartAIBehaviour.h"
#include "ThrowerAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "Transform.h"
#include "ModuleAudio.h"

#define RUN_START_DELAY 0.5f

ThrowerRunStartAIBehaviour::ThrowerRunStartAIBehaviour()
	: AIBehaviour(RUN_START) {}

ThrowerRunStartAIBehaviour::~ThrowerRunStartAIBehaviour()
{
	// No hace nada
}

void ThrowerRunStartAIBehaviour::OnEnter()
{
	ThrowerAIManager* throwerManager = (ThrowerAIManager*)manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador que indica la duración del breve periodo antes de huir
	timer.SetTimer(RUN_START_DELAY);

	// Detiene al personaje mientras empieza a correr
	entity->transform->speed.x = 0.0f;

	// Reproduce el sonido
	App->audio->PlayFx(throwerManager->runStartSound);
}

void ThrowerRunStartAIBehaviour::OnTick()
{
	// Cuando esté listo, huye
	if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, RUN);
}

void ThrowerRunStartAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
}