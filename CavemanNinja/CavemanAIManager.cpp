#include "CavemanAIManager.h"
#include "CircleColliderComponent.h"
#include "EntityLifetimeComponent.h"
#include "Entity.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "FlagEqualsCondition.h"
#include "CavemanIdleAIBehaviour.h"
#include "CavemanSearchAIBehaviour.h"
#include "CavemanChargeAIBehaviour.h"
#include "CavemanAttackAIBehaviour.h"
#include "CavemanRunStartAIBehaviour.h"
#include "CavemanRunAIBehaviour.h"

CavemanAIManager::CavemanAIManager(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent, AIState* initialState, float frecuency)
	: EnemyAIManager(initialState, frecuency) {
	this->attackComponent = attackComponent;
	this->hitboxComponent = hitboxComponent;
}

CavemanAIManager::~CavemanAIManager()
{
	// No hace nada
}

bool CavemanAIManager::OnStart()
{
	// Desactiva el collider de ataque
	if (attackComponent == NULL)
		return false;
	attackComponent->Disable();

	// Desactiva el componente de lifetime
	lifetimeComponent = entity->FindComponent<EntityLifetimeComponent>();
	if (lifetimeComponent == NULL)
		return false;
	lifetimeComponent->Disable();

	// Carga los efectos de sonido
	runStartSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run_start.wav");
	runSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run.wav");

	return hitboxComponent != NULL;
}

bool CavemanAIManager::OnCleanUp()
{
	// Desactiva el collider de ataque
	if (attackComponent == NULL)
		return false;
	attackComponent->Disable();

	return true;
}

CavemanAIManager * CavemanAIManager::Create(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent)
{
	// Crea los estados
	AIState* idle = new AIState(new CavemanIdleAIBehaviour());
	AIState* search = new AIState(new CavemanSearchAIBehaviour());
	AIState* charge = new AIState(new CavemanChargeAIBehaviour());
	AIState* attack = new AIState(new CavemanAttackAIBehaviour());
	AIState* startRun = new AIState(new CavemanRunStartAIBehaviour());
	AIState* run = new AIState(new CavemanRunAIBehaviour());

	// Crea las transiciones
	idle->AddStateTransition(new AITransition(search, new FlagEqualsCondition(STATE, SEARCH)));

	search->AddStateTransition(new AITransition(idle, new FlagEqualsCondition(STATE, IDLE)));
	search->AddStateTransition(new AITransition(charge, new FlagEqualsCondition(STATE, CHARGE)));

	charge->AddStateTransition(new AITransition(search, new FlagEqualsCondition(STATE, SEARCH)));
	charge->AddStateTransition(new AITransition(attack, new FlagEqualsCondition(STATE, ATTACK)));

	attack->AddStateTransition(new AITransition(startRun, new FlagEqualsCondition(STATE, RUN_START)));

	startRun->AddStateTransition(new AITransition(run, new FlagEqualsCondition(STATE, RUN)));

	return new CavemanAIManager(attackComponent, hitboxComponent, idle, 10.0f);
}
