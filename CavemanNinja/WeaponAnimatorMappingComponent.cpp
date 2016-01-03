#include "WeaponAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "WeaponGravityComponent.h"

WeaponAnimatorMappingComponent::WeaponAnimatorMappingComponent()
{
	// En principio no hace nada
}

WeaponAnimatorMappingComponent::~WeaponAnimatorMappingComponent()
{
	// En principio no hace nada
}

bool WeaponAnimatorMappingComponent::OnStart()
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
	gravityComponent = entity->FindComponent<WeaponGravityComponent>();
	if (gravityComponent == NULL)
		return false;

	return true;
}

bool WeaponAnimatorMappingComponent::OnPostUpdate()
{
	if (animator == NULL || gravityComponent == NULL)
		return false;

	// Mapea la velocidad horizontal de la entidad al animator
	float speed = entity->transform->GetLocalSpeed().x;
	animator->SetFlagValue("speedX_absolute", abs(speed));

	// Mapea si la entidad está callendo o no
	animator->SetFlagValue("falling", gravityComponent->falling);

	// Mapea si la entidad está en el suelo o no
	animator->SetFlagValue("on_ground", gravityComponent->onGround);

	// Flipea el animator según la velocidad
	if (speed > 0)
		animator->SetFlip(SDL_FLIP_NONE);
	else if (speed < 0)
		animator->SetFlip(SDL_FLIP_HORIZONTAL);

	return true;
}
