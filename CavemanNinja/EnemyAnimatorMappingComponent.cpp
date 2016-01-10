#include "EnemyAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "DieOnPlayerAttackComponent.h"
#include "AICavemanComponent.h"

EnemyAnimatorMappingComponent::EnemyAnimatorMappingComponent()
{
	// En principio no hace nada
}

EnemyAnimatorMappingComponent::~EnemyAnimatorMappingComponent()
{
	// En principio no hace nada
}

bool EnemyAnimatorMappingComponent::OnStart()
{
	// Recupera el renderer de la entidad
	SpriteRendererComponent* renderer = entity->FindComponent<SpriteRendererComponent>();
	if (renderer == NULL)
		return false;
	// Recupera el animator del renderer
	animator = dynamic_cast<Animator*>(renderer->GetAnimation());
	if (animator == NULL)
		return false;

	// Recupera el componente de la vida del personaje
	lifeComponent = entity->FindComponent<DieOnPlayerAttackComponent>();
	if (lifeComponent == NULL)
		return false;

	// Recupera el componente de AI de la entidad
	AIComponent = entity->FindComponent<AICavemanComponent>();
	if (AIComponent == NULL)
		return false;

	return true;
}

bool EnemyAnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || lifeComponent == NULL || AIComponent == NULL)
		return false;

	// Mapea los atributos adecuados al animator
	// Mapea el estado del personaje
	animator->SetFlagValue("AI_state", AIComponent->GetState());

	// Mapea si el personaje está muriendo o no
	animator->SetFlagValue("decaying", lifeComponent->decaying);

	// Mapea si el personaje ha sido herido o no
	float speed = entity->transform->GetLocalSpeed().x;
	animator->SetFlagValue("hit_back", lifeComponent->dead && speed < 0);
	animator->SetFlagValue("hit_front", lifeComponent->dead && speed >= 0);

	// Flipea el animator según la orientacion
	if (!lifeComponent->dead)
	{
		if (AIComponent->GetOrientation() > 0)
			animator->SetFlip(SDL_FLIP_HORIZONTAL);
		else if (AIComponent->GetOrientation() < 0)
			animator->SetFlip(SDL_FLIP_NONE);
	}

	return true;
}

