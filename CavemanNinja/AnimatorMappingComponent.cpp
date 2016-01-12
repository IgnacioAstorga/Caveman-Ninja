#include "AnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "PlayerGravityComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerLifeComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "GameControllerComponent.h"

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
	gravityComponent = entity->FindComponent<PlayerGravityComponent>();
	if (gravityComponent == NULL)
		return false;

	// Recupera el componente de salto de la entidad
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();
	if (jumpComponent == NULL)
		return false;

	// Recupera el componente de movimiento de la entidad
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	if (inputComponent == NULL)
		return false;

	// Recupera el componente de vida de la entidad
	lifeComponent = entity->FindComponent<PlayerLifeComponent>();
	if (lifeComponent == NULL)
		return false;

	return true;
}

bool AnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || gravityComponent == NULL || jumpComponent == NULL)
		return false;

	// Mapea la velocidad horizontal del personaje al animator
	fPoint speed = entity->transform->GetLocalSpeed();
	animator->SetFlagValue("speedX_absolute", abs(speed.x), true);
	animator->SetFlagValue("speedY", speed.y, true);

	// Mapea si el personaje est� mirando hacia arriba o no
	animator->SetFlagValue("looking_up", jumpComponent->lookingUp);

	// Mapea si el personaje est� agachado o no
	animator->SetFlagValue("crouch", jumpComponent->crouch);

	// Mapea si el personaje est� saltando o no
	animator->SetFlagValue("jumping", jumpComponent->jumping && !jumpComponent->longJumping);
	animator->SetFlagValue("jumping_long", jumpComponent->jumping && jumpComponent->longJumping);

	// Mapea si el personaje est� callendo o no
	animator->SetFlagValue("falling", gravityComponent->falling);

	// Mapea si el personaje est� detenido o no
	animator->SetFlagValue("stopped", inputComponent->IsStopped());

	// Mapea si el personaje est� muerto o no
	animator->SetFlagValue("dead", lifeComponent->dead);

	// Mapea si el personaje se ha muerto de hambre o no
	animator->SetFlagValue("dead_harvest", lifeComponent->dead && lifeComponent->deathCause == HARVEST);

	// Mapea si el personaje est� muriendo o no
	animator->SetFlagValue("decaying", lifeComponent->decaying && lifeComponent->deathCause == DAMAGE);

	// Mapea si el personaje ha sido herido o no
	bool hitted = lifeComponent->hit && inputComponent->IsStopped();
	bool hitFromBack;
	if (speed.x > 0)
		hitFromBack = inputComponent->orientation == FORWARD;
	else
		hitFromBack = inputComponent->orientation == BACKWARD;
	animator->SetFlagValue("hit_back", hitted && hitFromBack);
	animator->SetFlagValue("hit_front", hitted && !hitFromBack);

	// Flipea el animator seg�n la velocidad
	if (!hitted)
	{
		if (speed.x > 0)
			animator->SetFlip(SDL_FLIP_NONE);
		else if (speed.x < 0)
			animator->SetFlip(SDL_FLIP_HORIZONTAL);
		else if (inputComponent->orientation == FORWARD)
			animator->SetFlip(SDL_FLIP_NONE);
		else if (inputComponent->orientation == BACKWARD)
			animator->SetFlip(SDL_FLIP_HORIZONTAL);			
	}

	// Mapea si ha ganado o no
	animator->SetFlagValue("victory", GameController->victory, true);

	return true;
}
