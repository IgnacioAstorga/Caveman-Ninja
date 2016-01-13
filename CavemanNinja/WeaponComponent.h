#ifndef __WEAPONCOMPONENT_H__
#define __WEAPONCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class PlayerInputComponent;
class PlayerJumpComponent;
class CircleColliderComponent;
class Animator;

class WeaponComponent : public Component
{
public:
	WeaponComponent(CircleColliderComponent* meleeComponent, fPoint meleeOffset, fPoint rangedOffset, float chargeTime, float delay, int maximumProjectileCount);
	virtual ~WeaponComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnPreUpdate();

	virtual Entity* GetWeaponProjectile(fPoint position, int projectileNumber) = 0;
	virtual Entity* GetChargedWeaponProjectile(fPoint position, int projectileNumber) = 0;
	virtual fPoint GetInitialSpeed() = 0;
	virtual fPoint GetInitialChargedSpeed() = 0;
	virtual unsigned int GetFireSound() = 0;

private:
	void MeleeAttack();
	void RangedAttack();

public:
	fPoint meleeOffset;
	fPoint rangedOffset;

	float delay;
	float currentDelay;
	int maximumProjectileCount;
	int projectileCount;
	float chargeTime;
	bool charging;

	Timer meleeTimer;
	Timer chargeTimer;

	Animator* animator;
	PlayerInputComponent* inputComponent;
	PlayerJumpComponent* jumpComponent;
	CircleColliderComponent* meleeComponent;

	unsigned int fireSound;
	unsigned int fireChargedSound;
	unsigned int chargeCompleteSound;
};
#endif //__WEAPONCOMPONENT_H__