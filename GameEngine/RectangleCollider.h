#ifndef __RECTANGLECOLLIDER_H__
#define __RECTANGLECOLLIDER_H__

#include "Collider.h"
#include "Point.h"

class RectangleCollider : public Collider
{
public:
	RectangleCollider(CollisionListener* listener, Transform* trasnform, float width, float height, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool start_enabled = true);
	~RectangleCollider();

	bool CallMe(Collider* self);
	bool CheckCollision(CircleCollider* other);
	bool CheckCollision(RectangleCollider* other);
	void DrawCollider();

public:
	fPoint GetCenter();
	float GetRotation();
	fPoint* GetPoints();

public:
	float width, height;
	float offsetX, offsetY;
	float rotation;
};

#endif // __RECTANGLECOLLIDER_H__