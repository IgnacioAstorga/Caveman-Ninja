#ifndef __WEAPONTOMAHAWK_H__
#define __WEAPONTOMAHAWK_H__

#include "WeaponComponent.h"

class WeaponTomahawk : public WeaponComponent
{
public:
	WeaponTomahawk(CircleColliderComponent* meleeComponent, fPoint meleeOffset);

protected:
	Entity* GetWeaponProjectile(fPoint position, int projectileNumber, bool up);
	Entity* GetChargedWeaponProjectile(fPoint position, int projectileNumber);
	fPoint GetInitialSpeed();
	fPoint GetInitialChargedSpeed();
	unsigned int GetFireSound();
};
#endif //__WEAPONTOMAHAWK_H__