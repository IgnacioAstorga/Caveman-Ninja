#include "WeaponComponent.h"
#include "Entity.h"
#include "PlayerInputComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerGravityComponent.h"
#include "SpriteRendererComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"
#include "Transform.h"
#include "Animator.h"

#include "SDL.h"

WeaponComponent::WeaponComponent(fPoint offset, fPoint initialSpeed, float delay, int maximumProjectileCount)
{
	this->offset = offset;
	this->initialSpeed = initialSpeed;
	this->delay = delay;
	this->maximumProjectileCount = maximumProjectileCount;
}

WeaponComponent::~WeaponComponent()
{
	// En principio no hace nada
}

bool WeaponComponent::OnStart()
{
	// Recupera el renderer de la entidad
	SpriteRendererComponent* renderer = entity->FindComponent<SpriteRendererComponent>();
	if (renderer == NULL)
		return false;
	// Recupera el animator del renderer
	animator = dynamic_cast<Animator*>(renderer->GetAnimation());
	if (animator == NULL)
		return false;

	// Carga el efecto de sonido
	fireSound = GetFireSound();

	// Obtiene los componentes del jugador
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();
	return inputComponent != NULL && jumpComponent != NULL;
}

bool WeaponComponent::OnPreUpdate()
{
	currentDelay += App->time->DeltaTime();

	// Si el personaje esta detenido, no puede disparar
	if (inputComponent->stopped)
		return true;

	// Comprueba si se ha pulsado el botón
	KeyState keyState = App->input->GetMouseButtonDown(SDL_BUTTON_LEFT);
	if (keyState != KEY_UP)
		return true;

	// Comprueba que el personaje pueda disparar
	if (currentDelay < delay || projectileCount >= maximumProjectileCount)
		return true;

	// Frena al personaje
	if (!jumpComponent->jumping && !jumpComponent->fallingComponent->falling)
	{
		entity->transform->speed.x = 0.0f;
		inputComponent->Stop(delay);
	}

	// Determina la posición del disparo
	fPoint position = entity->transform->GetGlobalPosition();
	position.x += inputComponent->orientation == FORWARD ? offset.x : -offset.x;
	position.y += jumpComponent->crouch == true ? offset.y / 2.0f : offset.y;

	// Crea el proyectil del disparo
	Entity* projectile = GetWeaponProjectile(position, projectileCount);
	if (jumpComponent->lookingUp)
		projectile->transform->SetGlobalSpeed(0.0f, -1.25f * initialSpeed.Norm());
	else
	{
		float horizontalSpeed = inputComponent->orientation == FORWARD ? initialSpeed.x : -initialSpeed.x;
		projectile->transform->SetGlobalSpeed(horizontalSpeed, initialSpeed.y);
	}
	projectile->Instantiate();
	currentDelay = 0;
	projectileCount++;

	// Reproduce el efecto de sonido
	App->audio->PlayFx(fireSound);

	// Activa el flag en el animator (se hace aquí en vez de en el mapping porque es un trigger)
	if (jumpComponent->lookingUp)
		animator->Trigger("weapon_attack_up");
	else
		animator->Trigger("weapon_attack");

	return true;
}
