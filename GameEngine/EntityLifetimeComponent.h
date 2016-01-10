#ifndef __ENTITYLIFETIMECOMPONENT_H__
#define __ENTITYLIFETIMECOMPONENT_H__

#include "Component.h"
#include "Timer.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Entity.h"

class EntityLifetimeComponent : public Component
{
public:
	EntityLifetimeComponent(float lifeTime, bool start_enabled = true) : Component(start_enabled)
	{
		this->lifeTime = lifeTime;
	}

	~EntityLifetimeComponent()
	{
		// En principio no hace nada
	}

	bool OnStart()
	{
		// Registra el timer
		App->time->RegisterTimer(&timer);

		// Inicia el timer
		timer.SetTimer(lifeTime, true);

		return true;
	}

	bool OnCleanUp()
	{
		// Desregistra el timer
		App->time->UnregisterTimer(&timer);

		return true;
	}

	bool OnUpdate()
	{
		// Destruye la entidad si ha pasado el tiempo
		if (timer.IsTimerExpired())
			entity->Destroy();

		return true;
	}

private:
	Timer timer;
	float lifeTime;
};

#endif // __ENTITYLIFETIMECOMPONENT_H__