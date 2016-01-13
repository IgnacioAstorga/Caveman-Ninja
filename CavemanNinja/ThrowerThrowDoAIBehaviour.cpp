#include "ThrowerThrowDoAIBehaviour.h"
#include "ThrowerAIManager.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"
#include "Entity.h"
#include "Transform.h"
#include "RollingBall.h"

#define THROW_OFFSET_HORIZONTAL 24.0f
#define THROW_OFFSET_VERTICAL -43.0f
#define ROCK_SPEED 100.0f
#define THROW_DURATION 0.75f

ThrowerThrowDoAIBehaviour::ThrowerThrowDoAIBehaviour()
	: AIBehaviour(THROW_DO) {}

ThrowerThrowDoAIBehaviour::~ThrowerThrowDoAIBehaviour()
{
	// No hace nada
}

void ThrowerThrowDoAIBehaviour::OnEnter()
{
	ThrowerAIManager* throwerManager = (ThrowerAIManager*)manager;

	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el contador que indica la duración del ataque
	timer.SetTimer(THROW_DURATION);

	// Detiene al personaje mientras ataca
	entity->transform->speed.x = 0.0f;

	// Crea la piedra y la lanza
	RollingBall* rock = new RollingBall("rolling_ball_" + entity->name);
	fPoint position = entity->transform->GetGlobalPosition();
	if (throwerManager->orientation == RIGHT)
	{
		rock->transform->SetPosition(position.x + THROW_OFFSET_HORIZONTAL, position.y + THROW_OFFSET_VERTICAL);
		rock->transform->SetSpeed(ROCK_SPEED, 0.0f);
	}
	else
	{
		rock->transform->SetPosition(position.x - THROW_OFFSET_HORIZONTAL, position.y + THROW_OFFSET_VERTICAL);
		rock->transform->SetSpeed(-ROCK_SPEED, 0.0f);
	}
	rock->Instantiate();

	// Reproduce el sonido
	App->audio->PlayFx(throwerManager->throwSound);
}

void ThrowerThrowDoAIBehaviour::OnTick()
{
	// Si ha terminado de atacar, empieza a huir
	if (timer.IsTimerExpired())
		manager->SetFlagValue(STATE, RUN_START);
}

void ThrowerThrowDoAIBehaviour::OnExit()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
}
