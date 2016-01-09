#ifndef __RECTANGLECOLLIDERCOMPONENT_H__
#define __RECTANGLECOLLIDERCOMPONENT_H__

#include "ColliderComponent.h"

class RectangleCollider;

class RectangleColliderComponent : public ColliderComponent
{
public:
	RectangleColliderComponent(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool basic = false, bool start_enabled = true);
	RectangleColliderComponent(float width, float height, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, float rotation = 0.0f, int type = -1, bool basic = false, bool start_enabled = true);
	virtual ~RectangleColliderComponent();

	bool OnStart();
	bool OnCleanUp();

public:
	void SetWidth(float width);
	void SetHeight(float height);
	void SetOffset(float offsetX, float offsetY);
	void SetRotation(float rotation);
	Collider* GetCollider();

private:
	float width, height;
	float offsetX, offsetY;
	float rotation;
	int type;
	bool basic;

	RectangleCollider* collider;
};

#endif // __RECTANGLECOLLIDERCOMPONENT_H__