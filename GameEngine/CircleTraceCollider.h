#ifndef __CIRCLETRACECOLLIDER_H__
#define __CIRCLETRACECOLLIDER_H__

#include "CircleCollider.h"
#include "Point.h"

class CircleTraceCollider : public CircleCollider
{
public:
	CircleTraceCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	CircleTraceCollider(CollisionListener* listener, Transform* transform, float radius, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	~CircleTraceCollider();

	bool CallMe(const Collider* self) const;
	bool CheckCollision(const CircleCollider* other) const;
	bool CheckCollision(const CircleTraceCollider* other) const;
	bool CheckCollision(const RectangleCollider* other) const;
	bool CheckCollision(const RectangleBasicCollider* other) const;
	bool CheckCollision(const LineCollider* other) const;
	void DrawCollider() const;

	bool OnStartCollider();
	void OnPostUpdate();

public:
	CircleCollider GetCircleCollider() const;
	RectangleCollider GetTraceCollider() const;

public:
	fPoint lastFramePosition;
};

#endif // __CIRCLETRACECOLLIDER_H__