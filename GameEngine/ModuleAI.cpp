#include "ModuleAI.h"
#include "AIManager.h"

ModuleAI::ModuleAI(bool start_enabled) : Module(start_enabled)
{
	// No hace nada
}

ModuleAI::~ModuleAI()
{
	// No hace nada
}

bool ModuleAI::Start()
{
	LOG("Starting AI Module");

	bool ret = true;

	for (list<AIManager*>::iterator it = managers.begin(); it != managers.end() && ret; ++it)
		ret = (*it)->Start();

	return ret;
}

update_status ModuleAI::Update()
{
	for (list<AIManager*>::iterator it = managers.begin(); it != managers.end(); ++it)
		(*it)->Update();

	return UPDATE_CONTINUE;
}

bool ModuleAI::CleanUp()
{
	LOG("Cleaning up AI Module");

	// Limpia la lista de managers
	bool ret = true;

	for (list<AIManager*>::iterator it = managers.begin(); it != managers.end() && ret; ++it)
		ret = (*it)->CleanUp();
	managers.clear();

	return ret;
}

void ModuleAI::RegisterAIManager(AIManager* manager)
{
	LOG("AI manager registration");

	if (find(managers.begin(), managers.end(), manager) == managers.end())
	{
		managers.push_back(manager);
		manager->Start();
	}
}

void ModuleAI::UnregisterAIManager(AIManager* manager)
{
	LOG("AI manager unregistration");

	if (find(managers.begin(), managers.end(), manager) != managers.end())
	{
		managers.remove(manager);
		manager->CleanUp();
	}
}