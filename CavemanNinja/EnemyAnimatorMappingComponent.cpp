#include "EnemyAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "DieOnPlayerAttackComponent.h"
#include "AIComponent.h"
#include "CavemanAIManager.h"
#include "Entity.h"
#include "Transform.h"

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
	aiManager = dynamic_cast<CavemanAIManager*>(entity->FindComponent<AIComponent>()->GetAIManager());
	if (aiManager == NULL)
		return false;

	return true;
}

bool EnemyAnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || lifeComponent == NULL || aiManager == NULL)
		return false;

	// Mapea los atributos adecuados al animator
	// Mapea el estado del personaje
	animator->SetFlagValue("AI_state", aiManager->GetActualState()->GetIdentifier());

	// Mapea si el personaje está muriendo o no
	animator->SetFlagValue("decaying", lifeComponent->decaying);

	// Mapea si el personaje ha sido herido o no
	fPoint speed = entity->transform->GetLocalSpeed();
	bool hitFromBack;
	if (speed.x > 0)
		hitFromBack = aiManager->orientation > 0;
	else
		hitFromBack = aiManager->orientation < 0;
	animator->SetFlagValue("hit_back", lifeComponent->dead && hitFromBack);
	animator->SetFlagValue("hit_front", lifeComponent->dead && !hitFromBack);

	// Flipea el animator según la orientacion
	if (aiManager->orientation > 0)
		animator->SetFlip(SDL_FLIP_HORIZONTAL);
	else if (aiManager->orientation < 0)
		animator->SetFlip(SDL_FLIP_NONE);

	return true;
}

