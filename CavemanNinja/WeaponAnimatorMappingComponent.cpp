#include "WeaponAnimatorMappingComponent.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"
#include "WeaponGravityComponent.h"
#include "Entity.h"
#include "Transform.h"

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

	// Recupera el componente de gravedad de la entidad
	gravityComponent = entity->FindComponent<WeaponGravityComponent>();
	if (gravityComponent == NULL)
		return false;

	return true;
}

bool WeaponAnimatorMappingComponent::OnPostUpdate()
{
	// Flipea la animación según la velocidad
	float speed = entity->transform->GetLocalSpeed().x;
	SpriteRendererComponent* renderer = entity->FindComponent<SpriteRendererComponent>();
	if (speed > 0)
		renderer->GetAnimation()->SetFlip(SDL_FLIP_NONE);
	else if (speed < 0)
		renderer->GetAnimation()->SetFlip(SDL_FLIP_HORIZONTAL);

	if (animator == NULL || gravityComponent == NULL)
		return true;	// No da error, no tiene por qué tener animator

	// Mapea la velocidad horizontal de la entidad al animator
	animator->SetFlagValue("speedX_absolute", abs(speed));

	// Mapea si la entidad está callendo o no
	animator->SetFlagValue("falling", gravityComponent->falling);

	// Mapea si la entidad está en el suelo o no
	animator->SetFlagValue("on_ground", gravityComponent->onGround);

	return true;
}
