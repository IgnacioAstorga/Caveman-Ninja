#include "ThrowerAIManager.h"
#include "EntityLifetimeComponent.h"
#include "Entity.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "FlagEqualsCondition.h"
#include "ThrowerIdleAIBehaviour.h"
#include "ThrowerThrowStartAIBehaviour.h"
#include "ThrowerThrowDoAIBehaviour.h"
#include "ThrowerRunStartAIBehaviour.h"
#include "ThrowerRunAIBehaviour.h"

ThrowerAIManager::ThrowerAIManager(ColliderComponent* hitboxComponent, AIState* initialState, float frecuency)
	: EnemyAIManager(initialState, frecuency) {
	this->hitboxComponent = hitboxComponent;
}

ThrowerAIManager::~ThrowerAIManager()
{
	// No hace nada
}

bool ThrowerAIManager::OnStart()
{
	// Desactiva el componente de lifetime
	lifetimeComponent = entity->FindComponent<EntityLifetimeComponent>();
	if (lifetimeComponent == NULL)
		return false;
	lifetimeComponent->Disable();

	// Carga los efectos de sonido
	throwSound = App->audio->LoadFx("assets/sounds/enemy_thrower_throw.wav");
	runStartSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run_start.wav");
	runSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run.wav");

	return hitboxComponent != NULL;
}

bool ThrowerAIManager::OnCleanUp()
{
	// En principio no hace nada
	return true;
}

ThrowerAIManager * ThrowerAIManager::Create(ColliderComponent* hitboxComponent)
{
	// Crea los estados
	AIState* idle = new AIState(new ThrowerIdleAIBehaviour());
	AIState* throwStart = new AIState(new ThrowerThrowStartAIBehaviour());
	AIState* throwDo = new AIState(new ThrowerThrowDoAIBehaviour());
	AIState* startRun = new AIState(new ThrowerRunStartAIBehaviour());
	AIState* run = new AIState(new ThrowerRunAIBehaviour());

	// Crea las transiciones
	idle->AddStateTransition(new AITransition(throwStart, new FlagEqualsCondition(STATE, THROW_START)));

	throwStart->AddStateTransition(new AITransition(throwDo, new FlagEqualsCondition(STATE, THROW_DO)));

	throwDo->AddStateTransition(new AITransition(startRun, new FlagEqualsCondition(STATE, RUN_START)));

	startRun->AddStateTransition(new AITransition(run, new FlagEqualsCondition(STATE, RUN)));

	return new ThrowerAIManager(hitboxComponent, idle, 10.0f);
}
