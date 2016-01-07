#include "UserInterfaceComponent.h"
#include "GUILifebarComponent.h"
#include "Entity.h"

bool UserInterfaceComponent::OnStart()
{
	// Crea la barra de vida
	lifebar = new Entity("lifebar", 24, 24);
	lifebar->AddComponent(new GUILifebarComponent());
	lifebar->Instantiate(entity);

	return true;
}