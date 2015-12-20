#include "ModuleGUI.h"
#include "GUIComponent.h"

ModuleGUI::ModuleGUI(bool start_enabled) : Module(start_enabled)
{
	// No hace nada
}

ModuleGUI::~ModuleGUI()
{
	// No hace nada
}

bool ModuleGUI::Start()
{
	LOG("Starting GUI Module");

	bool ret = true;

	for (list<GUIComponent*>::iterator it = guiComponents.begin(); it != guiComponents.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	return ret;
}

update_status ModuleGUI::PreUpdate()
{
	bool ret = true;

	for (list<GUIComponent*>::iterator it = guiComponents.begin(); it != guiComponents.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->GUIPreUpdate();

	if (ret == true)
		return UPDATE_CONTINUE;
	else
		return UPDATE_ERROR;
}

update_status ModuleGUI::Update()
{
	bool ret = true;

	for (list<GUIComponent*>::iterator it = guiComponents.begin(); it != guiComponents.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->GUIUpdate();

	if (ret == true)
		return UPDATE_CONTINUE;
	else
		return UPDATE_ERROR;
}

update_status ModuleGUI::PostUpdate()
{
	bool ret = true;

	for (list<GUIComponent*>::iterator it = guiComponents.begin(); it != guiComponents.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->GUIPostUpdate();

	if (ret == true)
		return UPDATE_CONTINUE;
	else
		return UPDATE_ERROR;
}

bool ModuleGUI::CleanUp()
{
	LOG("Cleaning up GUI Module");

	// Limpia la lista de animaciones
	bool ret = true;

	while (!guiComponents.empty() && ret)
	{
		GUIComponent* c = guiComponents.front();
		if (c->IsEnabled())
			ret = c->CleanUp();
	}
	guiComponents.clear();

	return ret;
}

void ModuleGUI::RegisterGUIComponent(GUIComponent* guiComponent)
{
	LOG("GUI component registration");

	if (find(guiComponents.begin(), guiComponents.end(), guiComponent) == guiComponents.end())
	{
		guiComponents.push_back(guiComponent);
		guiComponent->Start();
	}
}

void ModuleGUI::UnregisterGUIComponent(GUIComponent* guiComponent)
{
	LOG("GUI component unregistration");

	if (find(guiComponents.begin(), guiComponents.end(), guiComponent) != guiComponents.end())
	{
		guiComponents.remove(guiComponent);
		guiComponent->CleanUp();
	}
}