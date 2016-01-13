#include "EnemyBasicAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "DieOnPlayerAttackComponent.h"
#include "Entity.h"
#include "Transform.h"

EnemyBasicAnimatorMappingComponent::EnemyBasicAnimatorMappingComponent()
{
	// En principio no hace nada
}

EnemyBasicAnimatorMappingComponent::~EnemyBasicAnimatorMappingComponent()
{
	// En principio no hace nada
}

bool EnemyBasicAnimatorMappingComponent::OnStart()
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

	return true;
}

bool EnemyBasicAnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || lifeComponent == NULL)
		return false;

	// Mapea los atributos adecuados al animator
	// Mapea si el personaje está muriendo o no
	animator->SetFlagValue("decaying", lifeComponent->decaying);

	// Mapea si el personaje ha sido herido o no
	animator->SetFlagValue("hit_back", lifeComponent->dead);	// Esta entidad solo se considera golpeada por la espalda

	// Flipea el animator según la orientacion
	fPoint speed = entity->transform->GetLocalSpeed();
	if (speed.x > 0)
		animator->SetFlip(SDL_FLIP_HORIZONTAL);
	else if (speed.x < 0)
		animator->SetFlip(SDL_FLIP_NONE);

	return true;
}

