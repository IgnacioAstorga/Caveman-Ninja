#ifndef __SPAWNPICKUPONDEATHCOMPONENT_H__
#define __SPAWNPICKUPONDEATHCOMPONENT_H__

#include "Component.h"

enum PickupType;

class SpawnPickupOnDeathComponent : public Component
{
public:
	SpawnPickupOnDeathComponent(PickupType type);
	~SpawnPickupOnDeathComponent();

public:
	void Spawn();

public:
	PickupType type;
};
#endif	// __SPAWNPICKUPONDEATHCOMPONENT_H__