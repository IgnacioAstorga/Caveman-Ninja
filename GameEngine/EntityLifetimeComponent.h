#ifndef __ENTITYLIFETIMECOMPONENT_H__
#define __ENTITYLIFETIMECOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class EntityLifetimeComponent : public Component
{
public:
	EntityLifetimeComponent(float lifeTime, bool start_enabled = true);
	virtual ~EntityLifetimeComponent();

	bool OnStart();
	bool OnCleanUp();
	bool OnUpdate();

private:
	Timer timer;
	float lifeTime;
};

#endif // __ENTITYLIFETIMECOMPONENT_H__