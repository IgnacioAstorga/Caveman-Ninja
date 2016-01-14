#ifndef __WEAPONBOOMERANG_H__
#define __WEAPONBOOMERANG_H__

#include "WeaponComponent.h"

class WeaponBoomerang : public WeaponComponent
{
public:
	WeaponBoomerang(CircleColliderComponent* meleeComponent, fPoint meleeOffset);

protected:
	Entity* GetWeaponProjectile(fPoint position, int projectileNumber, bool up);
	Entity* GetChargedWeaponProjectile(fPoint position, int projectileNumber);
	fPoint GetInitialSpeed();
	fPoint GetInitialChargedSpeed();
	unsigned int GetFireSound();
};
#endif //__WEAPONBOOMERANG_H__