#include "AIManager.h"
#include "Application.h"
#include "ModuleTime.h"

AIManager::AIManager(AIState * initialState, float frecuency)
	: StateMachine(initialState)
{
	SetFrecuency(frecuency);
}

AIManager::~AIManager()
{
	// No hace nada
}

bool AIManager::Start()
{
	// Inicia el estado initial
	currentStateSwitcher->GetActualState()->Configure(this, entity);
	currentStateSwitcher->GetActualState()->OnEnter();

	// Registra e inicia el timer
	App->time->RegisterTimer(&delayTimer);
	delayTimer.SetTimer(delay);

	// Llama al delegado
	return OnStart();
}

bool AIManager::CleanUp()
{
	// Termina el estado actual
	currentStateSwitcher->GetActualState()->OnExit();

	// Desregistra el timer
	App->time->UnregisterTimer(&delayTimer);

	// Llama al delegado
	return OnCleanUp();
}

bool AIManager::Update()
{
	// Comprueba si debe hacer tick
	if (delayTimer.IsTimerExpired(true))
		// Hace tick al estado actual
		currentStateSwitcher->GetActualState()->OnTick();
	
	return true;
}

void AIManager::SetFrecuency(float frecuency)
{
	SetDelay(1.0f / frecuency);
}

void AIManager::SetDelay(float delay)
{
	this->delay = delay;
}

void AIManager::Configure(Entity * entity)
{
	this->entity = entity;
}

void AIManager::OnStateTransition(AIBehaviour * lastState, AIBehaviour * newState)
{
	// Termina el estado anterior e inicia el siguiente
	lastState->OnExit();
	newState->Configure(this, entity);
	newState->OnEnter();
}