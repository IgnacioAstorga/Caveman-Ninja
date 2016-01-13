#ifndef __ANIMATORMAPPINGCOMPONENT_H__
#define __ANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class SpriteRendererComponent;
class PlayerGravityComponent;
class PlayerJumpComponent;
class PlayerInputComponent;
class PlayerLifeComponent;
class WeaponComponent;

class AnimatorMappingComponent : public Component
{
public:
	AnimatorMappingComponent(SpriteRendererComponent* mainRendererComponent, SpriteRendererComponent* chargingRendererComponent, SpriteRendererComponent* armRendererComponent);
	virtual ~AnimatorMappingComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

private:
	void ConfigureAnimator(Animator* animator);

public:
	SpriteRendererComponent* mainRendererComponent;
	SpriteRendererComponent* chargingRendererComponent;
	SpriteRendererComponent* armRendererComponent;

	Animator* mainAnimator;
	Animator* chargingAnimator;
	Animator* armAnimator;

	PlayerGravityComponent* gravityComponent;
	PlayerJumpComponent* jumpComponent;
	PlayerInputComponent* inputComponent;
	PlayerLifeComponent* lifeComponent;
	WeaponComponent* weaponComponent;
};
#endif // __ANIMATORMAPPINGCOMPONENT_H__