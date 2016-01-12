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

	bool CallMe(const Collider* self) const;
	bool CheckCollision(const CircleCollider* other) const;
	bool CheckCollision(const RectangleBasicCollider* other) const;

	void DrawCollider() const;

public:
	fPoint GetExternalPositionFromCoordinates(fPoint coordinates) const;
	fPoint GetCenter() const;
	float GetRotation() const;
	fPoint* GetPoints() const;
};

#endif // __RECTANGLECOLLIDER_H__