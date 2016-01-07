#include "AnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "PlayerGravityComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerLifeComponent.h"

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
	float speed = entity->transform->GetLocalSpeed().x;
	animator->SetFlagValue("speedX_absolute", abs(speed));

	// Mapea si el personaje está mirando hacia arriba o no
	animator->SetFlagValue("looking_up", jumpComponent->lookingUp);

	// Mapea si el personaje está saltando o no
	animator->SetFlagValue("jumping", jumpComponent->jumping && !jumpComponent->longJumping);
	animator->SetFlagValue("jumping_long", jumpComponent->jumping && jumpComponent->longJumping);

	// Mapea si el personaje está callendo o no
	animator->SetFlagValue("falling", gravityComponent->falling);

	// Mapea si el personaje está detenido o no
	animator->SetFlagValue("stopped", inputComponent->IsStopped());

	// Mapea si el personaje está muerto o no
	animator->SetFlagValue("dead", lifeComponent->dead);

	// Mapea si el personaje se ha muerto de hambre o no
	animator->SetFlagValue("dead_harvest", lifeComponent->dead && lifeComponent->deathCause == HARVEST);

	// Mapea si el personaje está muriendo o no
	animator->SetFlagValue("decaying", lifeComponent->decaying && lifeComponent->deathCause == DAMAGE);

	// Mapea si el personaje está en el suelo o no
	animator->SetFlagValue("on_ground", gravityComponent->onGround);

	// Mapea si el personaje ha sido herido o no
	bool hitted = lifeComponent->hit && inputComponent->IsStopped();
	bool hitFromBack;
	if (speed > 0)
		hitFromBack = inputComponent->orientation == FORWARD;
	else
		hitFromBack = inputComponent->orientation == BACKWARD;
	animator->SetFlagValue("hit_back", hitted && hitFromBack);
	animator->SetFlagValue("hit_front", hitted && !hitFromBack);

	// Flipea el animator según la velocidad
	if (!hitted)
	{
		if (speed > 0)
			animator->SetFlip(SDL_FLIP_NONE);
		else if (speed < 0)
			animator->SetFlip(SDL_FLIP_HORIZONTAL);
	}

	return true;
}
