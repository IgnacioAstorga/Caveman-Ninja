#include "MovementSimpleComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleTime.h"

MovementSimpleComponent::MovementSimpleComponent(bool start_enabled)
	: Component(start_enabled)
{
	// En principio no hace nada
}

MovementSimpleComponent::~MovementSimpleComponent()
{
	// En principio no hace nada
}

bool MovementSimpleComponent::OnUpdate()
{
	fPoint newPosition = entity->transform->GetLocalPosition() + entity->transform->GetLocalSpeed() * App->time->DeltaTime();
	entity->transform->SetPosition(newPosition.x, newPosition.y);

	return true;
}