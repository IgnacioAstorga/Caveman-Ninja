#ifndef __PLAYERJUMPCOMPONENT_H__
#define __PLAYERJUMPCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class PlayerGravityComponent;
class PlayerInputComponent;
class RectangleBasicCollider;
class WeaponComponent;

class PlayerJumpComponent : public Component
{
public:
	PlayerJumpComponent(float jumpSpeed, float longJumpMultiplier = 1.0f);
	virtual ~PlayerJumpComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnPreUpdate();

private:
	void Jump();
	void LeapDown();

public:
	float jumpSpeed;
	float longJumpMultiplier;
	bool jumping;
	bool longJumping;
	bool lookingUp;
	bool crouch;
	bool leapingDown;

	Timer leapingDownTimer;

	PlayerGravityComponent* fallingComponent;
	PlayerInputComponent* inputComponent;
	RectangleBasicCollider* hitboxCollider;
	WeaponComponent* weaponComponent;

	float originalOffsetY;
	float originalHeight;

	unsigned int jumpLongSound;
};
#endif //__PLAYERJUMPCOMPONENT_H__