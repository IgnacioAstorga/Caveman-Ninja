#ifndef __WEAPONLIFESPANCOMPONENT_H__
#define __WEAPONLIFESPANCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class WeaponLifespanComponent : public Component
{
public:
	WeaponLifespanComponent(float lifeTime);
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
};
#endif // __WEAPONLIFESPANCOMPONENT_H__