#ifndef __CIRCLETRACECOLLIDER_H__
#define __CIRCLETRACECOLLIDER_H__

#include "CircleCollider.h"
#include "Point.h"

class CircleTraceCollider : public CircleCollider
{
public:
	CircleTraceCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	~CircleTraceCollider();

	bool CallMe(Collider* self);
	bool CheckCollision(CircleCollider* other);
	bool CheckCollision(CircleTraceCollider* other);
	bool CheckCollision(RectangleCollider* other);
	bool CheckCollision(LineCollider* other);
	void DrawCollider();

	bool OnStartCollider();
	void OnPostUpdate();

public:
	CircleCollider GetCircleCollider();
	RectangleCollider GetTraceCollider();

public:
	fPoint lastFramePosition;
};

#endif // __CIRCLETRACECOLLIDER_H__