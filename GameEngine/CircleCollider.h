#ifndef __CIRCLECOLLIDER_H__
#define __CIRCLECOLLIDER_H__

#include "Collider.h"
#include "Point.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	~CircleCollider();

	bool CallMe(Collider* self);
	bool CheckCollision(CircleCollider* other);
	bool CheckCollision(RectangleCollider* other);
	bool CheckCollision(LineCollider* other);
	void DrawCollider();

public:
	fPoint GetCenter();
	float GetRadius();

public:
	float radius;
	float offsetX, offsetY;
};

#endif // __CIRCLECOLLIDER_H__