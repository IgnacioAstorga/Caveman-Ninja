#include "GUIScoreTextComponent.h"
#include "Entity.h"
#include "GUITextRendererComponent.h"
#include "GameControllerComponent.h"

GUIScoreTextComponent::GUIScoreTextComponent()
{
	// En principio no hace nada
}

GUIScoreTextComponent::~GUIScoreTextComponent()
{
	// En principio no hace nada
}

bool GUIScoreTextComponent::OnStart()
{
	// Recupera el componente de texto de la entidad
	textRenderer = entity->FindComponent<GUITextRendererComponent>();

	storedScore = -1;

	return textRenderer != NULL;
}

bool GUIScoreTextComponent::OnPostUpdate()
{
	if (textRenderer == NULL)
		return false;

	// Actualiza el texto con la puntuación
	if (storedScore != GameController->score)
	{
		textRenderer->SetText(to_string(GameController->score));
		storedScore = GameController->score;
	}

	return true;
}
