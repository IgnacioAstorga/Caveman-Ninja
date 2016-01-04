#ifndef __WEAPONANIMATORMAPPINGCOMPONENT_H__
#define __WEAPONANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class WeaponGravityComponent;

class WeaponAnimatorMappingComponent : public Component
{
public:
	WeaponAnimatorMappingComponent();
	virtual ~WeaponAnimatorMappingComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	Animator* animator;
	WeaponGravityComponent* gravityComponent;
};
#endif // __WEAPONANIMATORMAPPINGCOMPONENT_H__