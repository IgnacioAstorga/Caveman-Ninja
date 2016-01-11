#include "AIComponent.h"
#include "Application.h"
#include "ModuleAI.h"
#include "AIManager.h"

AIComponent::AIComponent(AIManager * manager, bool start_enabled)
	: Component(start_enabled) {
	this->manager = manager;
}

AIComponent::~AIComponent()
{
	RELEASE(manager);
}

bool AIComponent::OnStart()
{
	// Configura el manager
	manager->Configure(entity);

	// Registra el manager en el módulo de IA
	App->ai->RegisterAIManager(manager);

	return true;
}

bool AIComponent::OnCleanUp()
{
	// Desregistra el manager en el módulo de IA
	App->ai->UnregisterAIManager(manager);

	return false;
}

AIManager * AIComponent::GetAIManager()
{
	return manager;
}
