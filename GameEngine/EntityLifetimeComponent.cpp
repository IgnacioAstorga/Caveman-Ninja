#include "EntityLifetimeComponent.h"
#include "Timer.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"

EntityLifetimeComponent::EntityLifetimeComponent(float lifeTime, bool start_enabled)
	: Component(start_enabled)
{
	this->lifeTime = lifeTime;
}

EntityLifetimeComponent::~EntityLifetimeComponent()
{
	// En principio no hace nada
}

bool EntityLifetimeComponent::OnStart()
{
	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Inicia el timer
	timer.SetTimer(lifeTime, true);

	return true;
}

bool EntityLifetimeComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);

	return true;
}

bool EntityLifetimeComponent::OnUpdate()
{
	// Destruye la entidad si ha pasado el tiempo
	if (timer.IsTimerExpired())
		entity->Destroy();

	return true;
}