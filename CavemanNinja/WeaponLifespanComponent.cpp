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
	duration = 0;
	return weaponComponent != NULL;
}

bool WeaponLifespanComponent::OnPostUpdate()
{
	duration += App->time->DeltaTime();
	if (duration >= lifeTime)
		entity->Destroy();	// Destuye la entidad
	return true;
}

void WeaponLifespanComponent::Reset()
{
	Reset(lifeTime);
}

void WeaponLifespanComponent::Reset(float lifeTime)
{
	this->duration = 0.0f;
	this->lifeTime = lifeTime;
}
