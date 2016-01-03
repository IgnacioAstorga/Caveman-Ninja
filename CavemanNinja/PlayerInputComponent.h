#ifndef __PLAYERINPUTCOMPONENT_H__
#define __PLAYERINPUTCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"

enum Orientation {
	FORWARD,
	BACKWARD
};

class ColliderComponent;
class Collider;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(float speed, ColliderType wallColliderType, ColliderComponent* colliderComponent, float step_size = 0.5f);
	virtual ~PlayerInputComponent();

protected:
	bool OnPreUpdate();
	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	void Stop(float duration);
	bool IsStopped();

public:
	float speed;
	bool stopped;
	float stoppedDuration;
	float stoppedTime;
	Orientation orientation;
	ColliderType wallColliderType;
	ColliderComponent* colliderComponent;
	float step_size;
};
#endif //__PLAYERINPUTCOMPONENT_H__