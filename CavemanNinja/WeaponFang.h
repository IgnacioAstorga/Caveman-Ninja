#ifndef __WEAPONFANG_H__
#define __WEAPONFANG_H__

#include "WeaponComponent.h"

class WeaponFang : public WeaponComponent
{
public:
	WeaponFang(CircleColliderComponent* meleeComponent, fPoint meleeOffset);

protected:
	Entity* GetWeaponProjectile(fPoint position, int projectileNumber, bool up);
	Entity* GetChargedWeaponProjectile(fPoint position, int projectileNumber);
	fPoint GetInitialSpeed();
	fPoint GetInitialChargedSpeed();
	unsigned int GetFireSound();
};
#endif //__WEAPONFANG_H__