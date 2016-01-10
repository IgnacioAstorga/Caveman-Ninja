#include "DinosaurEyeComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "Animator.h"
#include "SpriteRendererComponent.h"

DinosaurEyeComponent::DinosaurEyeComponent()
{
	// No hace nada
}

DinosaurEyeComponent::~DinosaurEyeComponent()
{
	// No hace nada
}

bool DinosaurEyeComponent::OnUpdate()
{
	// Comprueba si el jugador esta cerca
	if (entity->transform->GetGlobalPosition().x > GameController->player->transform->GetGlobalPosition().x)
		return true;

	// Activa el flag en el animator
	Animator* animator = dynamic_cast<Animator*>(entity->FindComponent<SpriteRendererComponent>()->GetAnimation());
	if (animator == NULL)
		return false;
	animator->Trigger("player_in_sight");

	// Desactiva el componente
	this->Disable();

	return true;
}