#ifndef __RECTANGLECOLLIDER_H__
#define __RECTANGLECOLLIDER_H__

#include "Collider.h"
#include "Point.h"

class RectangleCollider : public Collider
{
public:
	RectangleCollider(CollisionListener* listener, Transform* transform, float width, float height, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool start_enabled = true);
	RectangleCollider(CollisionListener* listener, Transform* transform, float width, float height, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool start_enabled = true);
	virtual ~RectangleCollider();

	virtual bool CallMe(Collider* self);
	virtual bool CheckCollision(CircleCollider* other);
	virtual bool CheckCollision(CircleTraceCollider* other);
	virtual bool CheckCollision(RectangleCollider* other);
	virtual bool CheckCollision(RectangleBasicCollider* other);
	virtual bool CheckCollision(LineCollider* other);

	virtual void DrawCollider();
	virtual void DrawCollider(SDL_Color color);

public:
	virtual fPoint GetCenter();
	virtual float GetRotation();
	virtual fPoint* GetPoints();
	virtual CircleCollider GetBoundingCircle();

public:
	float width, height;
	float offsetX, offsetY;
	float rotation;
};

#endif // __RECTANGLECOLLIDER_H__