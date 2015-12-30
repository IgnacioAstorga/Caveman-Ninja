#ifndef __LINECOLLIDERCOMPONENT_H__
#define __LINECOLLIDERCOMPONENT_H__

#include "ColliderComponent.h"
#include "LineCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Entity.h"
#include "Point.h"

class LineColliderComponent : public ColliderComponent
{
public:
	LineColliderComponent(vector<fPoint> points, float thickness, int type = -1, bool start_enabled = true) : ColliderComponent(start_enabled)
	{
		this->points = points;
		this->thickness = thickness;
		this->type = type;
	}

	~LineColliderComponent()
	{
		// En principio no hace nada
	}

	bool OnStart()
	{
		if (entity == nullptr)
			return false;

		// Crea un collider y lo registra
		collider = new LineCollider(entity, entity->transform, points, thickness, type);
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

	void SetThickness(float thickness)
	{
		this->thickness = thickness;
		collider->thickness = thickness;
	}

	void AddPoint(fPoint point)
	{
		points.push_back(point);
		collider->points.push_back(point);
	}

	void AddPoint(fPoint point, int index)
	{
		points.insert(points.begin() + index, point);
		collider->points.insert(points.begin() + index, point);
	}

	void SetPoint(fPoint point, int index)
	{
		points[index] = point;
		collider->points[index] = point;
	}

	void RemovePoint(int index)
	{
		points.erase(points.begin() + index);
		collider->points.erase(points.begin() + index);
	}

	Collider* GetCollider()
	{
		return collider;
	}

private:
	vector<fPoint> points;
	float thickness;
	LineCollider* collider;
	int type;
};

#endif // __LINECOLLIDERCOMPONENT_H__