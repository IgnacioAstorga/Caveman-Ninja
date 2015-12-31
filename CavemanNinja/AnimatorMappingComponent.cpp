#include "AnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "GravityAndCollisionWithGroundComponent.h"
#include "PlayerJumpComponent.h"

AnimatorMappingComponent::AnimatorMappingComponent()
{
	// En principio no hace nada
}

AnimatorMappingComponent::~AnimatorMappingComponent()
{
	// En principio no hace nada
}

bool AnimatorMappingComponent::OnStart()
{
	// Recupera el renderer de la entidad
	SpriteRendererComponent* renderer = entity->FindComponent<SpriteRendererComponent>();
	if (renderer == NULL)
		return false;
	// Recupera el animator del renderer
	animator = dynamic_cast<Animator*>(renderer->GetAnimation());
	if (animator == NULL)
		return false;

	// Recupera el componente de gravedad de la entidad
	gravityComponent = entity->FindComponent<GravityAndCollisionWithGroundComponent>();
	if (gravityComponent == NULL)
		return false;

	// Recupera el componente de salto de la entidad
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();
	if (jumpComponent == NULL)
		return false;

	return true;
}

bool AnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || gravityComponent == NULL || jumpComponent == NULL)
		return false;

	// Mapea la velocidad horizontal del personaje al animator
	float speed = entity->transform->GetLocalSpeed().x;
	animator->SetFlagValue("speedX_absolute", abs(speed));

	// Mapea si el personaje est� saltando o no
	animator->SetFlagValue("jumping", jumpComponent->jumping && !jumpComponent->longJumping);
	animator->SetFlagValue("jumping_long", jumpComponent->jumping && jumpComponent->longJumping);

	// Mapea si el personaje est� callendo o no
	animator->SetFlagValue("falling", gravityComponent->falling && entity->transform->GetLocalSpeed().y > 200.0f);

	// Flipea el animator seg�n la velocidad
	if (speed > 0)
		animator->SetFlip(SDL_FLIP_NONE);
	else if (speed < 0 )
		animator->SetFlip(SDL_FLIP_HORIZONTAL);

	return true;
}
