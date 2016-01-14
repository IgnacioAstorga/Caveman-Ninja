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
#include "SpriteRendererComponent.h"
#include "WeaponComponent.h"

#define ARM_OFFSET_X_FORWARD -32.0f
#define ARM_OFFSET_X_BACKWARD -16.0f
#define ARM_OFFSET_Y_STAND -54.0f
#define ARM_OFFSET_Y_CROUCH -44.0f

AnimatorMappingComponent::AnimatorMappingComponent(SpriteRendererComponent* mainRendererComponent, SpriteRendererComponent* chargingRendererComponent, SpriteRendererComponent* armRendererComponent)
{
	this->mainRendererComponent = mainRendererComponent;
	this->chargingRendererComponent = chargingRendererComponent;
	this->armRendererComponent = armRendererComponent;
}

AnimatorMappingComponent::~AnimatorMappingComponent()
{
	// En principio no hace nada
}

bool AnimatorMappingComponent::OnStart()
{
	if (mainRendererComponent == NULL || chargingRendererComponent == NULL || armRendererComponent == NULL)
		return false;

	// Recupera el animator del renderer principal
	mainAnimator = dynamic_cast<Animator*>(mainRendererComponent->GetAnimation());
	if (mainAnimator == NULL)
		return false;

	// Recupera el animator del renderer cargando
	chargingAnimator = dynamic_cast<Animator*>(chargingRendererComponent->GetAnimation());
	if (chargingAnimator == NULL)
		return false;

	// Recupera el animator del brazo
	armAnimator = dynamic_cast<Animator*>(armRendererComponent->GetAnimation());
	if (armAnimator == NULL)
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
	if (mainAnimator == NULL || chargingAnimator == NULL || armAnimator == NULL || gravityComponent == NULL || jumpComponent == NULL)
		return false;

	// Recupera el componente de ataque de la entidad
	weaponComponent = entity->FindComponent<WeaponComponent>();
	if (weaponComponent == NULL)	// El arma puede cambiar, hay que recuperarlo cada vez
		return false;

	// Mapea los animator
	ConfigureAnimator(mainAnimator);
	ConfigureAnimator(chargingAnimator);
	ConfigureAnimator(armAnimator);

	// Alterna entre las dos versiones del renderer
	mainRendererComponent->SetVisible(!weaponComponent->charging);
	chargingRendererComponent->SetVisible(weaponComponent->charging);
	armRendererComponent->SetVisible(weaponComponent->charging);

	// Coloca el brazo en la posición adecuada
	float offsetX = inputComponent->orientation == FORWARD ? ARM_OFFSET_X_FORWARD : ARM_OFFSET_X_BACKWARD;
	float offsetY = jumpComponent->crouch ? ARM_OFFSET_Y_CROUCH : ARM_OFFSET_Y_STAND;
	armRendererComponent->SetOffset(offsetX, offsetY);

	return true;
}

void AnimatorMappingComponent::ConfigureAnimator(Animator * animator)
{
	// Mapea la velocidad horizontal del personaje al animator
	fPoint speed = entity->transform->GetLocalSpeed();
	animator->SetFlagValue("speedX_absolute", abs(speed.x), true);
	animator->SetFlagValue("speedY", speed.y, true);

	// Mapea si el personaje está mirando hacia arriba o no
	animator->SetFlagValue("looking_up", jumpComponent->lookingUp);

	// Mapea si el personaje está agachado o no
	animator->SetFlagValue("crouch", jumpComponent->crouch);

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
	animator->SetFlagValue("decaying", lifeComponent->decaying && lifeComponent->deathCause != HARVEST);

	// Mapea si el personaje ha sido herido o no
	bool hitFromBack;
	if (speed.x > 0)
		hitFromBack = inputComponent->orientation == FORWARD;
	else
		hitFromBack = inputComponent->orientation == BACKWARD;
	animator->SetFlagValue("hit_back", lifeComponent->hit && hitFromBack);
	animator->SetFlagValue("hit_front", lifeComponent->hit && !hitFromBack);

	// Mapea si el personaje está exausto o no
	animator->SetFlagValue("exhausted", lifeComponent->exhausted);

	// Flipea el animator según la velocidad
	if (!lifeComponent->hit)
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

	// Mapea si tiene el ataque cargado o no
	animator->SetFlagValue("charging", weaponComponent->charging, true);
	animator->SetFlagValue("attack_charged", weaponComponent->charging && weaponComponent->chargeTimer.IsTimerExpired(), true);
}
