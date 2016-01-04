#ifndef __WEAPONCOMPONENT_H__
#define __WEAPONCOMPONENT_H__

#include "Component.h"

class PlayerInputComponent;
class PlayerJumpComponent;
class Animator;

class WeaponComponent : public Component
{
public:
	WeaponComponent(fPoint offset, fPoint initialSpeed, float delay, int maximumProjectileCount);
	virtual ~WeaponComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();

	virtual Entity* GetWeaponProjectile(fPoint position, int projectileNumber) = 0;
	virtual unsigned int GetFireSound() = 0;

public:
	fPoint offset;
	fPoint initialSpeed;
	float delay;
	int maximumProjectileCount;
	Animator* animator;
	PlayerInputComponent* inputComponent;
	PlayerJumpComponent* jumpComponent;
	unsigned int fireSound;

	float currentDelay;
	int projectileCount;
};
#endif //__WEAPONCOMPONENT_H__