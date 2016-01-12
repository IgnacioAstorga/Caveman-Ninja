#ifndef __COLLIDERCOMPONENT_H__
#define __COLLIDERCOMPONENT_H__

#include "Component.h"

#include <vector>

class Collider;

using namespace std;

class ColliderComponent : public Component
{
public:
	ColliderComponent(bool start_enabled = true);
	ColliderComponent(vector<int> collisionsTypes, bool start_enabled = true);
	virtual ~ColliderComponent();

public:
	virtual Collider* GetCollider() const = 0;

public:
	bool hasSpecificCollisionsTypes;
	vector<int> collisionsTypes;
};

#endif // __COLLIDERCOMPONENT_H__