#include "RectangleColliderComponent.h"
#include "RectangleCollider.h"
#include "RectangleBasicCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"

RectangleColliderComponent::RectangleColliderComponent(float width, float height, float offsetX, float offsetY, float rotation, int type, bool basic, bool start_enabled) 
	: ColliderComponent(start_enabled)
{
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->rotation = rotation;
	this->type = type;
	this->basic = basic;
}

RectangleColliderComponent::RectangleColliderComponent(float width, float height, vector<int> collisionsTypes, float offsetX, float offsetY, float rotation, int type, bool basic, bool start_enabled)
	: ColliderComponent(collisionsTypes, start_enabled)
{
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->rotation = rotation;
	this->type = type;
	this->basic = basic;
}


RectangleColliderComponent::~RectangleColliderComponent()
{
	// En principio no hace nada
}

bool RectangleColliderComponent::OnStart()
{
	if (entity == nullptr)
		return false;

	// Crea un collider y lo registra
	if (hasSpecificCollisionsTypes)
	{
		if (basic)
			collider = new RectangleBasicCollider(entity, entity->transform, width, height, collisionsTypes, offsetX, offsetY, type);
		else
			collider = new RectangleCollider(entity, entity->transform, width, height, collisionsTypes, offsetX, offsetY, rotation, type);
	}
	else
	{
		if (basic)
			collider = new RectangleBasicCollider(entity, entity->transform, width, height, offsetX, offsetY, type);
		else
			collider = new RectangleCollider(entity, entity->transform, width, height, offsetX, offsetY, rotation, type);
	}
	collider->Start();
	App->collisions->RegisterCollider(collider);

	return true;
}

bool RectangleColliderComponent::OnCleanUp()
{
	if (collider == nullptr || entity == nullptr)
		return false;

	// Desregistra el collider y lo destruye
	App->collisions->UnregisterCollider(collider);
	collider->CleanUp();
	RELEASE(collider);

	return true;
}

void RectangleColliderComponent::SetWidth(float width)
{
	this->width = width;
	collider->width = width;
}

void RectangleColliderComponent::SetHeight(float height)
{
	this->height = height;
	collider->height = height;
}

void RectangleColliderComponent::SetOffset(float offsetX, float offsetY)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	collider->offsetX = offsetX;
	collider->offsetY = offsetY;
}

void RectangleColliderComponent::SetRotation(float rotation)
{
	this->rotation = rotation;
	collider->rotation = rotation;
}

Collider* RectangleColliderComponent::GetCollider()
{
	return collider;
}