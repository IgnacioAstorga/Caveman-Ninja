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

	virtual bool CallMe(const Collider* self) const;
	virtual bool CheckCollision(const CircleCollider* other) const;
	virtual bool CheckCollision(const CircleTraceCollider* other) const;
	virtual bool CheckCollision(const RectangleCollider* other) const;
	virtual bool CheckCollision(const RectangleBasicCollider* other) const;
	virtual bool CheckCollision(const LineCollider* other) const;

	virtual void DrawCollider() const;
	virtual void DrawCollider(SDL_Color color) const;

public:
	virtual fPoint GetExternalPositionFromCoordinates(fPoint coordinates) const;
	virtual fPoint GetCenter() const;
	virtual float GetRotation() const;
	virtual fPoint* GetPoints() const;
	virtual CircleCollider GetBoundingCircle() const;

public:
	float width, height;
	float offsetX, offsetY;
	float rotation;
};

#endif // __RECTANGLECOLLIDER_H__