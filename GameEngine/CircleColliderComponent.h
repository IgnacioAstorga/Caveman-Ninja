#ifndef __CIRCLECOLLIDERCOMPONENT_H__
#define __CIRCLECOLLIDERCOMPONENT_H__

#include "ColliderComponent.h"

class CircleCollider;

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent(float radius, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool trace = false, bool start_enabled = true);
	CircleColliderComponent(float radius, vector<int> collisionsTypes, float offsetX = 0.0f, float offsetY = 0.0f, int type = -1, bool trace = false, bool start_enabled = true);
	virtual ~CircleColliderComponent();

	bool OnStart();
	bool OnCleanUp();

public:
	void SetRadius(float radius);
	void SetOffset(float offsetX, float offsetY);
	Collider* GetCollider();

private:
	float radius;
	float offsetX, offsetY;
	int type;
	bool trace;

	CircleCollider* collider;
};

#endif // __CIRCLECOLLIDERCOMPONENT_H__