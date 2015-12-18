#ifndef __CIRCLECOLLIDERCOMPONENT_H__
#define __CIRCLECOLLIDERCOMPONENT_H__

#include "Component.h"
#include "CircleCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"

class CircleColliderComponent : public Component
{
public:
	CircleColliderComponent(float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true) : Component(start_enabled)
	{
		this->radius = radius;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->type = type;
	}

	~CircleColliderComponent()
	{
		// En principio no hace nada
	}

	bool OnStart()
	{
		if (entity == nullptr)
			return false;

		// Crea un collider y lo registra
		collider = new CircleCollider(entity, entity->transform, radius, offsetX, offsetY, type);
		collider->Start();
		App->collisions->RegisterCollider(collider);

		return true;
	}

	bool OnCleanUp()
	{
		if (collider == nullptr || entity == nullptr)
			return false;

		// Desregistra el collider y lo destruye
		App->collisions->UnregisterCollider(collider);
		collider->CleanUp();
		RELEASE(collider);

		return true;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
		collider->radius = radius;
	}

	void SetOffset(float offsetX, float offsetY)
	{
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		collider->offsetX = offsetX;
		collider->offsetY = offsetY;
	}

private:
	float radius;
	float offsetX, offsetY;
	CircleCollider* collider;
	int type;
};

#endif // __CIRCLECOLLIDERCOMPONENT_H__