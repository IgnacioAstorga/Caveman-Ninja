#ifndef __WEAPONLIFESPANCOMPONENT_H__
#define __WEAPONLIFESPANCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class WeaponComponent;

class WeaponLifespanComponent : public Component
{
public:
	WeaponLifespanComponent(float lifeTime, WeaponComponent* weaponComponent);
	virtual ~WeaponLifespanComponent();

protected:
	bool OnStart();
	bool OnCleanUp();

	bool OnPostUpdate();

public:
	void Reset();
	void Reset(float lifeTime);

public:
	float lifeTime;
	Timer lifetimeTimer;

	WeaponComponent* weaponComponent;
};
#endif // __WEAPONLIFESPANCOMPONENT_H__