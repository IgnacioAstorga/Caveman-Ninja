#include "ActivateComponentAfterTimeComponent.h"
#include "Application.h"
#include "ModuleTime.h"

ActivateComponentAfterTimeComponent::ActivateComponentAfterTimeComponent(float time, Component * component, bool start_enabled)
	: Component(start_enabled)
{
	this->time = time;
	components.push_back(component);
}

ActivateComponentAfterTimeComponent::ActivateComponentAfterTimeComponent(float time, vector<Component*> components, bool start_enabled)
	: Component(start_enabled)
{
	this->time = time;
	this->components = components;
}

ActivateComponentAfterTimeComponent::~ActivateComponentAfterTimeComponent()
{
	components.clear();
}

bool ActivateComponentAfterTimeComponent::OnStart()
{
	// Registra e inicia el timer
	App->time->RegisterTimer(&timer);
	timer.SetTimer(time);
	return true;	// OJO, no desactiva los componentes previamente
}

bool ActivateComponentAfterTimeComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);
	return true;
}

bool ActivateComponentAfterTimeComponent::OnPreUpdate()
{
	// Si ha pasado el tiempo suficiente, activa los componentes y se desactiva él mismo
	if (timer.IsTimerExpired())
	{
		for (vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
			(*it)->Enable();
		this->Disable();
	}
	return true;
}
