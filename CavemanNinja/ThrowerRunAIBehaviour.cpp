#include "ThrowerRunAIBehaviour.h"
#include "ThrowerAIManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "EntityLifetimeComponent.h"
#include "ColliderComponent.h"

#define RUN_SPEED 300.0f

ThrowerRunAIBehaviour::ThrowerRunAIBehaviour()
	: AIBehaviour(RUN) {}

ThrowerRunAIBehaviour::~ThrowerRunAIBehaviour()
{
	// No hace nada
}

void ThrowerRunAIBehaviour::OnEnter()
{
	ThrowerAIManager* throwerManager = (ThrowerAIManager*)manager;

	// Huye en dirección opuesta
	throwerManager->orientation = -1 * throwerManager->orientation;
	entity->transform->speed.x = throwerManager->orientation * RUN_SPEED;

	// Desactiva la hitbox del personaje
	throwerManager->hitboxComponent->Disable();

	// Activa el componente de desaparición del personaje
	throwerManager->lifetimeComponent->Enable();

	// Reproduce el sonido
	App->audio->PlayFx(throwerManager->runSound);
}

void ThrowerRunAIBehaviour::OnTick()
{
	// No hace nada
}

void ThrowerRunAIBehaviour::OnExit()
{
	// No hace nada
}