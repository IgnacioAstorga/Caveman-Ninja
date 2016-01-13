#include "UserInterfaceComponent.h"
#include "GUILifebarComponent.h"
#include "Entity.h"
#include "GUIPortrait.h"
#include "GUIScoreTextComponent.h"
#include "GUITextRendererComponent.h"
#include "Transform.h"

#define LIFE_INCREASE 9

bool UserInterfaceComponent::OnStart()
{
	// Crea la barra de vida
	lifebar = new Entity("lifebar", 24, 24);
	lifebar->AddComponent(new GUILifebarComponent(LIFE_INCREASE));
	lifebar->Instantiate(entity);

	// Crea el retrato
	portrait = new GUIPortrait("portrait", 0, 8);
	portrait->Instantiate(entity);

	// Crea el texto de la puntuación
	score = new Entity("score", 98, 23);
	score->AddComponent(new GUITextRendererComponent("0", "assets/fonts/PressStart2P.ttf", 12, WHITE, BOTTOM_RIGHT, 0.0f, 0.0f, TOP_LEFT, true, { 1.0f, 1.0f }));
	score->AddComponent(new GUIScoreTextComponent());
	score->transform->SetScale(0.5f);
	score->Instantiate(entity);

	// Crea la etiqueta del jugador
	playerLabel = new Entity("label", 24, 23);
	playerLabel->AddComponent(new GUITextRendererComponent("1 PL", "assets/fonts/PressStart2P.ttf", 12, WHITE, BOTTOM_LEFT, 0.0f, 0.0f, TOP_LEFT, true, { 1.0f, 1.0f }));
	playerLabel->transform->SetScale(0.5f);
	playerLabel->Instantiate(entity);

	return true;
}