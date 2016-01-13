#ifndef __TOMAHAWKBIGPROJECTILE_H__
#define __TOMAHAWKBIGPROJECTILE_H__

#include "Entity.h"

class WeaponComponent;

class TomahawkBigProjectile : public Entity
{
public:
	TomahawkBigProjectile(WeaponComponent* weaponComponent, std::string name, float positionX = 0.0f, float positionY = 0.0f);
	~TomahawkBigProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	WeaponComponent* weaponComponent;
};
#endif	// __TOMAHAWKBIGPROJECTILE_H__