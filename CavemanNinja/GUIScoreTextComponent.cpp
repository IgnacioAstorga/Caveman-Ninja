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
	textRenderers = entity->FindAllComponents<GUITextRendererComponent>();

	storedScore = -1;

	return !textRenderers.empty();
}

bool GUIScoreTextComponent::OnPostUpdate()
{
	if (textRenderers.empty())
		return false;

	// Actualiza el texto con la puntuación
	if (storedScore != GameController->score)
	{
		for (list<GUITextRendererComponent*>::iterator it = textRenderers.begin(); it != textRenderers.end(); ++it)
			(*it)->SetText(to_string(GameController->score));
		storedScore = GameController->score;
	}

	return true;
}
