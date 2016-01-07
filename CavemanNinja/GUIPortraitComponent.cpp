#include "GUIPortraitComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "PlayerLifeComponent.h"
#include "Animator.h"
#include "GUISpriteRendererComponent.h"

GUIPortraitComponent::GUIPortraitComponent()
{
	// En principio no hace nada
}

GUIPortraitComponent::~GUIPortraitComponent()
{
	// En principio no hace nada
}

bool GUIPortraitComponent::OnStart()
{
	// Obtiene el componente de vida del jugador
	lifeComponent = GameController->player->FindComponent<PlayerLifeComponent>();

	// Obtiene el animator del retrato
	animator = dynamic_cast<Animator*>(entity->FindComponent<GUISpriteRendererComponent>()->GetAnimation());

	return animator != NULL && lifeComponent != NULL;
}

bool GUIPortraitComponent::OnPostUpdate()
{
	if (animator == NULL || lifeComponent == NULL)
		return false;

	// Actualiza en el animator el estado del retrato
	if (lifeComponent->dead)
		animator->SetFlagValue("player_status", DEAD);
	else if (lifeComponent->hit)
		animator->SetFlagValue("player_status", HIT);
	else
		animator->SetFlagValue("player_status", IDLE);

	return true;
}
