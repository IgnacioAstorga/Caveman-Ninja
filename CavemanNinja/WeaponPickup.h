#ifndef __WEAPONPICKUP_H__
#define __WEAPONPICKUP_H__

#include "Entity.h"

enum WeaponPickupType
{
	WEAPON_TOMAHAWK = 0,
	WEAPON_FANG = 1,
	WEAPON_BOOMERANG = 2
};

class WeaponPickup : public Entity
{
public:
	WeaponPickup(WeaponPickupType type, string name, float positionX = 0.0f, float positionY = 0.0f);
	~WeaponPickup() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	WeaponPickupType type;
};
#endif	// __WEAPONPICKUP_H__