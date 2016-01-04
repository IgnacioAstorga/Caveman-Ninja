#include "EnemyAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "DieOnPlayerAttackComponent.h"

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

	return true;
}

bool EnemyAnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL)
		return false;

	// Mapea los atributos adecuados al animator
	if (lifeComponent != NULL)
	{
		animator->SetFlagValue("dead", lifeComponent->dead);
		animator->SetFlagValue("decaying", lifeComponent->decaying);
	}

	return true;
}

