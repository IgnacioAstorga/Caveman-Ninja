#ifndef __SPAWNPEGGONDEATHCOMPONENT_H__
#define __SPAWNPEGGONDEATHCOMPONENT_H__

#include "SpawnEntityOnDeathComponent.h"
#include "Egg.h"

class SpawnEggOnDeathComponent : public SpawnEntityOnDeathComponent
{
public:
	SpawnEggOnDeathComponent() {};
	virtual ~SpawnEggOnDeathComponent() {};

protected:
	Entity * SpawnEggOnDeathComponent::GetEntity()
	{
		return new Egg("egg_" + entity->name);
	}
};
#endif	// __SPAWNPEGGONDEATHCOMPONENT_H__