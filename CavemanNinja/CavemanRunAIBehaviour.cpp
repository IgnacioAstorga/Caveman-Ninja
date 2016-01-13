#include "CavemanRunAIBehaviour.h"
#include "CavemanAIManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "EntityLifetimeComponent.h"
#include "ColliderComponent.h"

#define RUN_SPEED 300.0f

CavemanRunAIBehaviour::CavemanRunAIBehaviour()
	: AIBehaviour(RUN) {}

CavemanRunAIBehaviour::~CavemanRunAIBehaviour()
{
	// No hace nada
}

void CavemanRunAIBehaviour::OnEnter()
{
	CavemanAIManager* cavemanManager = (CavemanAIManager*)manager;

	// Huye en dirección opuesta
	cavemanManager->orientation = -1 * cavemanManager->orientation;
	entity->transform->speed.x = cavemanManager->orientation * RUN_SPEED;

	// Desactiva la hitbox del personaje
	cavemanManager->hitboxComponent->Disable();

	// Activa el componente de desaparición del personaje
	cavemanManager->lifetimeComponent->Enable();

	// Reproduce el sonido
	App->audio->PlayFx(cavemanManager->runSound);
}

void CavemanRunAIBehaviour::OnTick()
{
	// No hace nada
}

void CavemanRunAIBehaviour::OnExit()
{
	// No hace nada
}