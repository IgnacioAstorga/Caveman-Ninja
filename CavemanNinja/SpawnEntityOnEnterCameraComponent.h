#ifndef __SPAWNENTITYONENTERCAMERACOMPONENT_H__
#define __SPAWNENTITYONENTERCAMERACOMPONENT_H__

#include "Component.h"

class SpawnEntityOnEnterCameraComponent : public Component
{
public:
	SpawnEntityOnEnterCameraComponent(Entity* spawnedEntity);
	virtual ~SpawnEntityOnEnterCameraComponent();

protected:
	bool OnUpdate();

public:
	bool spawned;
	Entity* spawnedEntity;
};
#endif	// __SPAWNENTITYONENTERCAMERACOMPONENT_H__