#ifndef __PLAYERINPUTCOMPONENT_H__
#define __PLAYERINPUTCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

enum Orientation {
	FORWARD,
	BACKWARD
};

class PlayerJumpComponent;
class ColliderComponent;
class Collider;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(float speed, ColliderComponent* colliderComponent, float step_size = 0.5f);
	virtual ~PlayerInputComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnPreUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);

public:
	void Stop(float duration);
	bool IsStopped();

public:
	float speed;
	bool stopped;
	Orientation orientation;

	Timer stopTimer;

	PlayerJumpComponent* jumpComponent;
	ColliderComponent* colliderComponent;

	float step_size;
};
#endif //__PLAYERINPUTCOMPONENT_H__