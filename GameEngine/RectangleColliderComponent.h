#ifndef __RECTANGLECOLLIDERCOMPONENT_H__
#define __RECTANGLECOLLIDERCOMPONENT_H__

#include "Component.h"
#include "RectangleCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"

class RectangleColliderComponent : public Component
{
public:
	RectangleColliderComponent(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool start_enabled = true) : Component(start_enabled)
	{
		this->width = width;
		this->height = height;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->rotation = rotation;
		this->type = type;
	}

	~RectangleColliderComponent()
	{
		// En principio no hace nada
	}

	bool OnStart()
	{
		if (entity == nullptr)
			return false;

		// Crea un collider y lo registra
		collider = new RectangleCollider(entity, entity->transform, width, height, offsetX, offsetY, rotation, type);
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

	void SetWidth(float width)
	{
		this->width = width;
		collider->width = width;
	}

	void SetHeight(float height)
	{
		this->height = height;
		collider->height = height;
	}

	void SetOffset(float offsetX, float offsetY)
	{
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		collider->offsetX = offsetX;
		collider->offsetY = offsetY;
	}

	void SetRotation(float rotation)
	{
		this->rotation = rotation;
		collider->rotation = rotation;
	}

private:
	float width, height;
	float offsetX, offsetY;
	float rotation;
	RectangleCollider* collider;
	int type;
};

#endif // __RECTANGLECOLLIDERCOMPONENT_H__