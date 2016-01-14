#ifndef __SPAWNPICKUPONDEATHCOMPONENT_H__
#define __SPAWNPICKUPONDEATHCOMPONENT_H__

#include "Component.h"

enum PickupType;

class SpawnPickupOnDeathComponent : public Component
{
public:
	SpawnPickupOnDeathComponent(int type);
	virtual ~SpawnPickupOnDeathComponent();

public:
	void Spawn();

protected:
	virtual Entity* GetPickup(int type) = 0;

public:
	int type;
};
#endif	// __SPAWNPICKUPONDEATHCOMPONENT_H__