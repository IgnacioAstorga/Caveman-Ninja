#ifndef __ANIMATORMAPPINGCOMPONENT_H__
#define __ANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class GravityAndCollisionWithGroundComponent;
class PlayerJumpComponent;

class AnimatorMappingComponent : public Component
{
public:
	AnimatorMappingComponent();
	virtual ~AnimatorMappingComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	Animator* animator;
	GravityAndCollisionWithGroundComponent* gravityComponent;
	PlayerJumpComponent* jumpComponent;
};
#endif // __ANIMATORMAPPINGCOMPONENT_H__