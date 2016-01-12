#include "LineColliderComponent.h"
#include "LineCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"
#include "Point.h"

LineColliderComponent::LineColliderComponent(vector<fPoint> points, float thickness, int type, bool start_enabled)
	: ColliderComponent(start_enabled)
{
	this->points = points;
	this->thickness = thickness;
	this->type = type;
}

LineColliderComponent::LineColliderComponent(vector<fPoint> points, float thickness, vector<int> collisionsTypes, int type, bool start_enabled)
	: ColliderComponent(collisionsTypes, start_enabled)
{
	this->points = points;
	this->thickness = thickness;
	this->type = type;
}

LineColliderComponent::~LineColliderComponent()
{
	// En principio no hace nada
}

bool LineColliderComponent::OnStart()
{
	if (entity == nullptr)
		return false;

	// Crea un collider y lo registra
	if (hasSpecificCollisionsTypes)
		collider = new LineCollider(entity, entity->transform, points, thickness, collisionsTypes, type);
	else
		collider = new LineCollider(entity, entity->transform, points, thickness, type);
	collider->Start();
	App->collisions->RegisterCollider(collider);

	return true;
}

bool LineColliderComponent::OnCleanUp()
{
	if (collider == nullptr || entity == nullptr)
		return false;

	// Desregistra el collider y lo destruye
	App->collisions->UnregisterCollider(collider);
	collider->CleanUp();
	RELEASE(collider);

	return true;
}

void LineColliderComponent::SetThickness(float thickness)
{
	this->thickness = thickness;
	collider->thickness = thickness;
}

void LineColliderComponent::AddPoint(fPoint point)
{
	points.push_back(point);
	collider->points.push_back(point);
}

void LineColliderComponent::AddPoint(fPoint point, int index)
{
	points.insert(points.begin() + index, point);
	collider->points.insert(points.begin() + index, point);
}

void LineColliderComponent::SetPoint(fPoint point, int index)
{
	points[index] = point;
	collider->points[index] = point;
}

void LineColliderComponent::RemovePoint(int index)
{
	points.erase(points.begin() + index);
	collider->points.erase(points.begin() + index);
}

Collider* LineColliderComponent::GetCollider() const
{
	return collider;
}