#ifndef __CIRCLECOLLIDERCOMPONENT_H__
#define __CIRCLECOLLIDERCOMPONENT_H__

#include "ColliderComponent.h"
#include "CircleCollider.h"
#include "CircleTraceCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent(float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool trace = false, bool start_enabled = true) : ColliderComponent(start_enabled)
	{
		this->radius = radius;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->type = type;
		this->trace = trace;
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
		if (trace)
			collider = new CircleTraceCollider(entity, entity->transform, radius, offsetX, offsetY, type);
		else
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

	Collider* GetCollider()
	{
		return collider;
	}

private:
	float radius;
	float offsetX, offsetY;
	CircleCollider* collider;
	int type;
	bool trace;
};

#endif // __CIRCLECOLLIDERCOMPONENT_H__