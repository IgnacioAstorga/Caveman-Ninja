#ifndef __WEAPONLIFESPANCOMPONENT_H__
#define __WEAPONLIFESPANCOMPONENT_H__

#include "Component.h"

class WeaponComponent;

class WeaponLifespanComponent : public Component
{
public:
	WeaponLifespanComponent(float lifeTime, WeaponComponent* weaponComponent);
	virtual ~WeaponLifespanComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	void Reset();
	void Reset(float lifeTime);

public:
	float lifeTime;
	float duration;
	WeaponComponent* weaponComponent;
};
#endif // __WEAPONLIFESPANCOMPONENT_H__