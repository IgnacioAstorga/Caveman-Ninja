#include "WeaponComponent.h"
#include "Entity.h"
#include "PlayerInputComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerGravityComponent.h"
#include "PlayerLifeComponent.h"
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
#include "SDL_mixer.h"

#define UP_FACTOR -1.25f
#define EXHAUST_TIME 5.0f

#define CHARGE_SOUND_CHANNEL 1	// Canal reservado 1

WeaponComponent::WeaponComponent(CircleColliderComponent* meleeComponent, fPoint meleeOffset, fPoint rangedOffset, float chargeTime, float delay, int maximumProjectileCount)
{
	this->meleeComponent = meleeComponent;
	this->meleeOffset = meleeOffset;
	this->rangedOffset = rangedOffset;
	this->chargeTime = chargeTime;
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

	// Carga los efectos de sonido
	fireSound = GetFireSound();
	fireChargedSound = App->audio->LoadFx("assets/sounds/player_attack_big.wav");
	chargeCompleteSound = App->audio->LoadFx("assets/sounds/player_charge_complete.wav");

	// Registra el timer del ataque cuerpo a cuerpo y del ataque cargado
	App->time->RegisterTimer(&chargeTimer);
	App->time->RegisterTimer(&exhaustTimer);
	App->time->RegisterTimer(&meleeTimer);
	meleeComponent->Disable();

	// Obtiene los componentes del jugador
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();
	lifeComponent = entity->FindComponent<PlayerLifeComponent>();

	charging = false;

	return inputComponent != NULL && jumpComponent != NULL && meleeComponent != NULL;
}

bool WeaponComponent::OnCleanUp()
{
	// Desregistra el timer del ataque cuerpo a cuerpo y del ataque cargado
	App->time->UnregisterTimer(&chargeTimer);
	App->time->UnregisterTimer(&exhaustTimer);
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

	// Si la carga está completa, reproduce une fecto de sonido
	if (charging && chargeTimer.IsTimerExpired())
	{
		if (!Mix_Playing(CHARGE_SOUND_CHANNEL))
			App->audio->PlayFx(chargeCompleteSound, -1, CHARGE_SOUND_CHANNEL);
	}
	else
		Mix_HaltChannel(CHARGE_SOUND_CHANNEL);

	// Si el personaje esta detenido, no puede disparar
	if (inputComponent->stopped)
	{
		// Deja de cargar el ataque
		charging = false;
		return true;
	}

	// Comprueba el estado del botón
	KeyState keyState = App->input->GetMouseButtonDown(SDL_BUTTON_LEFT);
	if (keyState == KEY_IDLE)
		return true;

	// Comprueba que el personaje pueda disparar
	if (currentDelay < delay)
		return true;

	// Comrpueba si está cargando el ataque
	if (keyState == KEY_DOWN || keyState == KEY_REPEAT)
	{
		if (!charging && !jumpComponent->longJumping)	// No puede cargar si está haciendo salto largo
		{
			// Empieza a cargar el ataque
			charging = true;
			chargeTimer.SetTimer(chargeTime);
			exhaustTimer.SetTimer(EXHAUST_TIME);
		}
		else if (charging && exhaustTimer.IsTimerExpired())
		{
			// El personaje se cansa
			lifeComponent->Exhaust();
		}
		return true;
	}

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
		y = 2.0f * meleeOffset.y - abs(meleeOffset.x);
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
	charging = false;
	currentDelay = 0;
}

void WeaponComponent::RangedAttack()
{
	// Comprueba si el ataque está cargado
	bool chargeComplete = charging && chargeTimer.IsTimerExpired();
	charging = false;

	// Determina la posición del disparo
	fPoint position = entity->transform->GetGlobalPosition();
	if (!jumpComponent->lookingUp || chargeComplete)
		position.x += inputComponent->orientation == FORWARD ? rangedOffset.x : -rangedOffset.x;
	position.y += jumpComponent->crouch == true ? rangedOffset.y / 2.0f : rangedOffset.y;

	// Crea el proyectil del disparo
	fPoint speed;
	Entity* projectile;
	if (chargeComplete)
	{
		projectile = GetChargedWeaponProjectile(position, projectileCount);
		speed = GetInitialChargedSpeed();
	}
	else
	{
		projectile = GetWeaponProjectile(position, projectileCount, jumpComponent->lookingUp);
		speed = GetInitialSpeed();
	}

	// Lo configura
	if (jumpComponent->lookingUp && !chargeComplete)	// No puede disparar ataques cargados hacia arriba
		projectile->transform->SetGlobalSpeed(0.0f, UP_FACTOR * speed.Norm());
	else
	{
		float horizontalSpeed = inputComponent->orientation == FORWARD ? speed.x : -speed.x;
		projectile->transform->SetGlobalSpeed(horizontalSpeed, speed.y);
	}
	projectile->Instantiate();
	projectileCount++;

	// Reproduce el efecto de sonido
	App->audio->PlayFx(fireSound);
	if (chargeComplete)
		App->audio->PlayFx(fireChargedSound);

	// Activa el flag en el animator (se hace aquí en vez de en el mapping porque es un trigger)
	if (chargeComplete)
			animator->Trigger("weapon_attack_charged");
	else
	{
		if (jumpComponent->lookingUp)
			animator->Trigger("weapon_attack_up");
		else
			animator->Trigger("weapon_attack");
	}

	// Reestablece el delay del ataque
	currentDelay = 0;
}
