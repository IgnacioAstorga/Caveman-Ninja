#ifndef __RECTANGLEBASICCOLLIDER_H__
#define __RECTANGLEBASICCOLLIDER_H__

#include "RectangleCollider.h"
#include "Point.h"

class RectangleBasicCollider : public RectangleCollider
{
public:
	RectangleBasicCollider(CollisionListener* listener, Transform* transform, float width, float height, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	RectangleBasicCollider(CollisionListener* listener, Transform* transform, float width, float height, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool start_enabled = true);
	~RectangleBasicCollider();

	bool CallMe(Collider* self);
	bool CheckCollision(CircleCollider* other);
	bool CheckCollision(RectangleBasicCollider* other);

	void DrawCollider();

public:
	fPoint GetCenter();
	float GetRotation();
	fPoint* GetPoints();
};

#endif // __RECTANGLECOLLIDER_H__