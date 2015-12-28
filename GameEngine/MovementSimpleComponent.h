#ifndef __MOVEMENTSIMPLECOMPONENT_H__
#define __MOVEMENTSIMPLECOMPONENT_H__

#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleTime.h"

class MovementSimpleComponent : public Component
{
public:
	MovementSimpleComponent(bool start_enabled = true) : Component(start_enabled)
	{
		// En principio no hace nada
	}

	~MovementSimpleComponent()
	{
		// En principio no hace nada
	}

	bool OnUpdate()
	{
		fPoint newPosition = entity->transform->GetLocalPosition() + entity->transform->GetLocalSpeed() * App->time->DeltaTime();
		entity->transform->SetPosition(newPosition.x, newPosition.y);

		return true;
	}
};

#endif // __MOVEMENTSIMPLECOMPONENT_H__