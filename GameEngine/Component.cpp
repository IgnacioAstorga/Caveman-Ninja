#include "Component.h"
#include "Entity.h"

Component::Component(bool start_enabled) : enabled(start_enabled)
{
	// Llamada al delegado
	OnCreate();
}

Component::~Component()
{
	// Llamada al delegado
	OnDestroy();
}

Component* Component::Create(Entity* entity)
{
	entity->AddComponent(this);

	return this;
}

bool Component::IsEnabled()
{
	return enabled;
}

bool Component::Enable()
{
	if (enabled == false)
		return enabled = Start();

	return true;
}

bool Component::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();

	return true;
}

Entity* Component::GetEntity()
{
	return entity;
}

void Component::SetEntity(Entity* entity)
{
	if (entity == nullptr) {
		if (this->entity != nullptr)
			this->entity->RemoveComponent(this);
		this->entity = nullptr;
	}
	else
		entity->AddComponent(this);
}
