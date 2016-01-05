#include "EffectLifespanComponent.h"
#include "Entity.h"
#include "Application.h"
#include "ModuleTime.h"

EffectLifespanComponent::EffectLifespanComponent(float lifeTime)
{
	this->lifeTime = lifeTime;
}

EffectLifespanComponent::~EffectLifespanComponent()
{
	// No hace nada
}

bool EffectLifespanComponent::OnStart()
{
	duration = 0.0f;
	return true;
}

bool EffectLifespanComponent::OnPostUpdate()
{
	duration += App->time->DeltaTime();
	if (duration >= lifeTime)
		entity->Destroy();	// Destuye la entidad
	return true;
}

void EffectLifespanComponent::Reset()
{
	Reset(lifeTime);
}

void EffectLifespanComponent::Reset(float lifeTime)
{
	this->duration = 0.0f;
	this->lifeTime = lifeTime;
}
