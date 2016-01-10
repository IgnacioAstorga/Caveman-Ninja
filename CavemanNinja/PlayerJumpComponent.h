#ifndef __PLAYERJUMPCOMPONENT_H__
#define __PLAYERJUMPCOMPONENT_H__

#include "Component.h"

class PlayerGravityComponent;
class PlayerInputComponent;
class RectangleBasicCollider;

class PlayerJumpComponent : public Component
{
public:
	PlayerJumpComponent(float jumpSpeed, float longJumpMultiplier = 1.0f);
	virtual ~PlayerJumpComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();

private:
	void Jump();

public:
	float jumpSpeed;
	float longJumpMultiplier;
	bool jumping;
	bool longJumping;
	bool lookingUp;
	bool crouch;

	PlayerGravityComponent* fallingComponent;
	PlayerInputComponent* inputComponent;
	RectangleBasicCollider* hitboxCollider;

	float originalOffsetY;
	float originalHeight;

	unsigned int jumpLongSound;
};
#endif //__PLAYERJUMPCOMPONENT_H__