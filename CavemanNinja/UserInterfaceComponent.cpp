#include "UserInterfaceComponent.h"
#include "GUILifebarComponent.h"
#include "Entity.h"
#include "GUIPortrait.h"
#include "GUIScoreTextComponent.h"
#include "GUITextRendererComponent.h"
#include "Transform.h"

bool UserInterfaceComponent::OnStart()
{
	// Crea la barra de vida
	lifebar = new Entity("lifebar", 24, 24);
	lifebar->AddComponent(new GUILifebarComponent(18));
	lifebar->Instantiate(entity);

	// Crea el retrato
	portrait = new GUIPortrait("portrait", 0, 8);
	portrait->Instantiate(entity);

	// Crea el texto de la puntuación
	score = new Entity("score", 98, 23);
	score->AddComponent(new GUITextRendererComponent("", "assets/fonts/PressStart2P.ttf", 12, BLACK, BOTTOM_RIGHT, 2.0f, 1.0f));
	score->AddComponent(new GUITextRendererComponent("", "assets/fonts/PressStart2P.ttf", 12, WHITE, BOTTOM_RIGHT));
	score->AddComponent(new GUIScoreTextComponent());
	score->transform->SetScale(0.5f);
	score->Instantiate(entity);

	// Crea la etiqueta del jugador
	playerLabel = new Entity("label", 24, 23);
	playerLabel->AddComponent(new GUITextRendererComponent("1 PL", "assets/fonts/PressStart2P.ttf", 12, BLACK, BOTTOM_LEFT, 2.0f, 1.0f));
	playerLabel->AddComponent(new GUITextRendererComponent("1 PL", "assets/fonts/PressStart2P.ttf", 12, WHITE, BOTTOM_LEFT));
	playerLabel->transform->SetScale(0.5f);
	playerLabel->Instantiate(entity);

	return true;
}