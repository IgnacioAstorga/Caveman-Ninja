#include "WeaponLifespanComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"
#include "WeaponComponent.h"

WeaponLifespanComponent::WeaponLifespanComponent(float lifeTime, WeaponComponent* weaponComponent)
{
	this->lifeTime = lifeTime;
	this->weaponComponent = weaponComponent;
}

WeaponLifespanComponent::~WeaponLifespanComponent()
{
	// Reduce en uno la cuenta de proyectiles disparados
	weaponComponent->projectileCount -= 1;
}

bool WeaponLifespanComponent::OnStart()
{
	// Registra el timer y lo inicia
	App->time->RegisterTimer(&lifetimeTimer);
	lifetimeTimer.SetTimer(lifeTime);

	return weaponComponent != NULL;
}

bool WeaponLifespanComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&lifetimeTimer);

	return true;
}

bool WeaponLifespanComponent::OnPostUpdate()
{
	if (lifetimeTimer.IsTimerExpired())
		entity->Destroy();	// Destuye la entidad
	return true;
}

void WeaponLifespanComponent::Reset()
{
	Reset(lifeTime);
}

void WeaponLifespanComponent::Reset(float lifeTime)
{
	lifetimeTimer.SetTimer(lifeTime);
}
