#ifndef __PLAYERJUMPCOMPONENT_H__
#define __PLAYERJUMPCOMPONENT_H__

#include "Component.h"

class PlayerGravityComponent;
class PlayerInputComponent;

class PlayerJumpComponent : public Component
{
public:
	PlayerJumpComponent(float jumpSpeed, float longJumpMultiplier = 1.0f);
	virtual ~PlayerJumpComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();

public:
	float jumpSpeed;
	float longJumpMultiplier;
	bool jumping;
	bool longJumping;
	bool lookingUp;

	PlayerGravityComponent* fallingComponent;
	PlayerInputComponent* inputComponent;

	unsigned int jumpLongSound;
};
#endif //__PLAYERJUMPCOMPONENT_H__