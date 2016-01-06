#ifndef __ANIMATORMAPPINGCOMPONENT_H__
#define __ANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class PlayerGravityComponent;
class PlayerJumpComponent;
class PlayerInputComponent;
class PlayerLifeComponent;

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
	PlayerGravityComponent* gravityComponent;
	PlayerJumpComponent* jumpComponent;
	PlayerInputComponent* inputComponent;
	PlayerLifeComponent* lifeComponent;
};
#endif // __ANIMATORMAPPINGCOMPONENT_H__