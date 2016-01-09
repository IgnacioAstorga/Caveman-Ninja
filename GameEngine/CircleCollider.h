#ifndef __CIRCLECOLLIDER_H__
#define __CIRCLECOLLIDER_H__

#include "Collider.h"
#include "Point.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	CircleCollider(CollisionListener* listener, Transform* transform, float radius, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	virtual ~CircleCollider();

	virtual bool CallMe(Collider* self);

	virtual bool CheckCollision(CircleCollider* other);
	virtual bool CheckCollision(CircleTraceCollider* other);
	virtual bool CheckCollision(RectangleCollider* other);
	virtual bool CheckCollision(RectangleBasicCollider* other);
	virtual bool CheckCollision(LineCollider* other);

	virtual void DrawCollider();

public:
	virtual fPoint GetExternalPositionFromCoordinates(fPoint coordinates);
	virtual fPoint GetCenter();
	virtual float GetRadius();

public:
	float radius;
	float offsetX, offsetY;
};

#endif // __CIRCLECOLLIDER_H__