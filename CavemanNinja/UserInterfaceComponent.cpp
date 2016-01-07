#include "UserInterfaceComponent.h"
#include "GUILifebarComponent.h"
#include "Entity.h"
#include "GUIPortrait.h"

bool UserInterfaceComponent::OnStart()
{
	// Crea la barra de vida
	lifebar = new Entity("lifebar", 24, 24);
	lifebar->AddComponent(new GUILifebarComponent());
	lifebar->Instantiate(entity);

	// Crea el retrato
	portrait = new GUIPortrait("portrait", 0, 8);
	portrait->Instantiate(entity);

	return true;
}