#ifndef __TOMAHAWKPROJECTILE_H__
#define __TOMAHAWKPROJECTILE_H__

#include "Entity.h"

class WeaponComponent;

class TomahawkProjectile : public Entity
{
public:
	TomahawkProjectile(WeaponComponent* weaponComponent, std::string name, float positionX = 0.0f, float positionY = 0.0f);
	~TomahawkProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	WeaponComponent* weaponComponent;
};
#endif	// __TOMAHAWKPROJECTILE_H__