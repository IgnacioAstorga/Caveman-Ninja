#include "GUIComponent.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "Entity.h"
#include "Transform.h"

GUIComponent::GUIComponent(GUILocation location, bool start_enabled) : Component(start_enabled)
{
	this->location = location;
}

GUIComponent::~GUIComponent()
{
	// En principio no hace nada
}

bool GUIComponent::OnStart()
{
	App->gui->RegisterGUIComponent(this);
	return GUIStart();
}

bool GUIComponent::OnCleanUp()
{
	App->gui->UnregisterGUIComponent(this);
	return GUICleanUp();
}

bool GUIComponent::GUIStart()
{ 
	return true;
};

bool GUIComponent::GUIPreUpdate() 
{
	return true;
};

bool GUIComponent::GUIUpdate() 
{
	return true;
};

bool GUIComponent::GUIPostUpdate() 
{
	return true;
};

bool GUIComponent::GUICleanUp()
{
	return true;
};