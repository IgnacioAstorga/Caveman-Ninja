#include "CircleColliderComponent.h"
#include "CircleCollider.h"
#include "CircleTraceCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"

CircleColliderComponent::CircleColliderComponent(float radius, float offsetX, float offsetY, int type, bool trace, bool start_enabled)
	: ColliderComponent(start_enabled)
{
	this->radius = radius;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->type = type;
	this->trace = trace;
}

CircleColliderComponent::CircleColliderComponent(float radius, vector<int> collisionsTypes, float offsetX, float offsetY, int type, bool trace, bool start_enabled)
	: ColliderComponent(collisionsTypes, start_enabled)
{
	this->radius = radius;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->type = type;
	this->trace = trace;
}

CircleColliderComponent::~CircleColliderComponent()
{
	// En principio no hace nada
}

bool CircleColliderComponent::OnStart()
{
	if (entity == nullptr)
		return false;

	// Crea un collider y lo registra
	if (hasSpecificCollisionsTypes)
	{
		if (trace)
			collider = new CircleTraceCollider(entity, entity->transform, radius, collisionsTypes, offsetX, offsetY, type);
		else
			collider = new CircleCollider(entity, entity->transform, radius, collisionsTypes, offsetX, offsetY, type);
	}
	else
	{
		if (trace)
			collider = new CircleTraceCollider(entity, entity->transform, radius, offsetX, offsetY, type);
		else
			collider = new CircleCollider(entity, entity->transform, radius, offsetX, offsetY, type);
	}
	collider->Start();
	App->collisions->RegisterCollider(collider);

	return true;
}

bool CircleColliderComponent::OnCleanUp()
{
	if (collider == nullptr || entity == nullptr)
		return false;

	// Desregistra el collider y lo destruye
	App->collisions->UnregisterCollider(collider);
	collider->CleanUp();
	RELEASE(collider);

	return true;
}

void CircleColliderComponent::SetRadius(float radius)
{
	this->radius = radius;
	collider->radius = radius;
}

void CircleColliderComponent::SetOffset(float offsetX, float offsetY)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	collider->offsetX = offsetX;
	collider->offsetY = offsetY;
}

Collider* CircleColliderComponent::GetCollider() const
{
	return collider;
}