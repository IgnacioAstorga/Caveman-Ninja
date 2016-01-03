#ifndef __PLAYERJUMPCOMPONENT_H__
#define __PLAYERJUMPCOMPONENT_H__

#include "Component.h"

class GravityAndCollisionWithGroundComponent;

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
	GravityAndCollisionWithGroundComponent* fallingComponent;
	bool jumping;
	bool longJumping;
	bool lookingUp;
	unsigned int jumpSound;
	unsigned int jumpLongSound;
};
#endif //__PLAYERJUMPCOMPONENT_H__