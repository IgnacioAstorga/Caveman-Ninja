#ifndef __SPAWNENTITYONDEATHCOMPONENT_H__
#define __SPAWNENTITYONDEATHCOMPONENT_H__

#include "Component.h"

class SpawnEntityOnDeathComponent : public Component
{
public:
	SpawnEntityOnDeathComponent();
	virtual ~SpawnEntityOnDeathComponent();

public:
	void Spawn();

protected:
	virtual Entity* GetEntity() = 0;
};
#endif	// __SPAWNENTITYONDEATHCOMPONENT_H__