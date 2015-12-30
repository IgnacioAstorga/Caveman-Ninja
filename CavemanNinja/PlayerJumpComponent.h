#ifndef __PLAYERJUMPCOMPONENT_H__
#define __PLAYERJUMPCOMPONENT_H__

#include "Component.h"

class GravityAndCollisionWithGroundComponent;

class PlayerJumpComponent : public Component
{
public:
	PlayerJumpComponent(float jumpSpeed);
	virtual ~PlayerJumpComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();

public:
	float jumpSpeed;
	GravityAndCollisionWithGroundComponent* fallingComponent;
	bool jumping;
};
#endif //__PLAYERJUMPCOMPONENT_H__