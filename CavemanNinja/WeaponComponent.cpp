#include "WeaponComponent.h"
#include "Entity.h"
#include "PlayerInputComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerGravityComponent.h"
#include "SpriteRendererComponent.h"
#include "CircleColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"
#include "Transform.h"
#include "Animator.h"

#include "SDL.h"

WeaponComponent::WeaponComponent(CircleColliderComponent* meleeComponent, fPoint meleeOffset, fPoint rangedOffset, fPoint initialSpeed, float delay, int maximumProjectileCount)
{
	this->meleeComponent = meleeComponent;
	this->meleeOffset = meleeOffset;
	this->rangedOffset = rangedOffset;
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

	// Registra el timer del ataque cuerpo a cuerpo
	App->time->RegisterTimer(&meleeTimer);
	meleeComponent->Disable();

	// Obtiene los componentes del jugador
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();

	return inputComponent != NULL && jumpComponent != NULL && meleeComponent != NULL;
}

bool WeaponComponent::OnCleanUp()
{
	// Desregistra el timer del ataque cuerpo a cuerpo
	App->time->UnregisterTimer(&meleeTimer);
	meleeComponent->Disable();

	return true;
}

bool WeaponComponent::OnPreUpdate()
{
	currentDelay += App->time->DeltaTime();

	// Si el timer del ataque cuerpo a cuerpo ha expirado, desactiva el collider
	if (meleeTimer.IsTimerExpired() && meleeComponent->IsEnabled())
		meleeComponent->Disable();

	// Si el personaje esta detenido, no puede disparar
	if (inputComponent->stopped)
		return true;

	// Comprueba si se ha pulsado el botón
	KeyState keyState = App->input->GetMouseButtonDown(SDL_BUTTON_LEFT);
	if (keyState != KEY_UP)
		return true;

	// Comprueba que el personaje pueda disparar
	if (currentDelay < delay)
		return true;

	// Frena al personaje
	if (!jumpComponent->jumping && !jumpComponent->fallingComponent->falling)
	{
		entity->transform->speed.x = 0.0f;
		inputComponent->Stop(delay);
	}

	// Determina si el personaje realizará un disparo o un ataque cuerpo a cuerpo
	if (projectileCount >= maximumProjectileCount)
		MeleeAttack();
	else
		RangedAttack();

	return true;
}

void WeaponComponent::MeleeAttack()
{
	// Si el personaje está haciendo un salto alto, aborta
	if (jumpComponent->longJumping)
		return;

	// Activa el collider
	if (!meleeComponent->IsEnabled())
		meleeComponent->Enable();

	// Determina la posición del collider
	float x;
	float y;
	if (jumpComponent->lookingUp)
	{
		x = 0.0f;
		y = 2.0f * meleeOffset.y;
	}
	else
	{
		x = inputComponent->orientation == FORWARD ? meleeOffset.x : -meleeOffset.x;
		y = jumpComponent->crouch == true ? meleeOffset.y / 2.0f : meleeOffset.y;
	}
	meleeComponent->SetOffset(x, y);

	// Inicia el timer del ataque cuerpo a cuerpo
	meleeTimer.SetTimer(delay / 2.0f);

	// Activa el flag en el animator (se hace aquí en vez de en el mapping porque es un trigger)
	if (jumpComponent->lookingUp)
		animator->Trigger("melee_attack_up");
	else
		animator->Trigger("melee_attack");

	// Reestablece el delay del ataque
	currentDelay = 0;
}

void WeaponComponent::RangedAttack()
{
	// Determina la posición del disparo
	fPoint position = entity->transform->GetGlobalPosition();
	position.x += inputComponent->orientation == FORWARD ? rangedOffset.x : -rangedOffset.x;
	position.y += jumpComponent->crouch == true ? rangedOffset.y / 2.0f : rangedOffset.y;

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
	projectileCount++;

	// Reproduce el efecto de sonido
	App->audio->PlayFx(fireSound);

	// Activa el flag en el animator (se hace aquí en vez de en el mapping porque es un trigger)
	if (jumpComponent->lookingUp)
		animator->Trigger("weapon_attack_up");
	else
		animator->Trigger("weapon_attack");

	// Reestablece el delay del ataque
	currentDelay = 0;
}
