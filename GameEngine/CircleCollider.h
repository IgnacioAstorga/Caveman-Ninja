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

	virtual bool CallMe(const Collider* self) const;

	virtual bool CheckCollision(const CircleCollider* other) const;
	virtual bool CheckCollision(const CircleTraceCollider* other) const;
	virtual bool CheckCollision(const RectangleCollider* other) const;
	virtual bool CheckCollision(const RectangleBasicCollider* other) const;
	virtual bool CheckCollision(const LineCollider* other) const;

	virtual void DrawCollider() const;

public:
	virtual fPoint GetExternalPositionFromCoordinates(fPoint coordinates) const;
	virtual fPoint GetCenter() const;
	virtual float GetRadius() const;

public:
	float radius;
	float offsetX, offsetY;
};

#endif // __CIRCLECOLLIDER_H__