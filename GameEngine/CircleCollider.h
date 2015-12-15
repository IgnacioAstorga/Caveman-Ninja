#ifndef __CIRCLECOLLIDER_H__
#define __CIRCLECOLLIDER_H__

#include "Collider.h"
#include "Transform.h"
#include "CollisionListener.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(CollisionListener* listener, Transform* trasnform, float radius, float offsetX = 0.0f, float offsetY = 0.0f, bool start_enabled = true) : Collider(listener, trasnform, start_enabled)
	{
		this->radius = radius;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	}

	~CircleCollider()
	{
		// No hace nada
	}

	bool Collider::CallMe(Collider* self)
	{
		return self->CheckCollision(this);
	}

	bool CheckCollision(CircleCollider* other)
	{
		// Comprueba si la distancia entre ambos centros es menor que la suma de sus radios
		return this->GetCenter().DistanceTo(other->GetCenter()) <= (this->radius + other->radius);
	}

	fPoint GetCenter()
	{
		return transform->GetGlobalPosition() + fPoint(offsetX, offsetY).Rotate(transform->GetGlobalRotation());
	}

public:
	float radius;
	float offsetX, offsetY;
};

#endif // __CIRCLECOLLIDER_H__