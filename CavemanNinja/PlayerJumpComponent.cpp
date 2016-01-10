#include "PlayerJumpComponent.h"
#include "PlayerGravityComponent.h"
#include "PlayerInputComponent.h"
#include "ColliderComponent.h"
#include "Collider.h"
#include "RectangleBasicCollider.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"

PlayerJumpComponent::PlayerJumpComponent(float jumpSpeed, float longJumpMultiplier)
{
	this->jumpSpeed = jumpSpeed;
	this->longJumpMultiplier = longJumpMultiplier;
}

PlayerJumpComponent::~PlayerJumpComponent()
{
	// En principio no hace nada
}

bool PlayerJumpComponent::OnStart()
{
	jumping = false;

	// Intenta recuperar el componente donde comprobar si se está callendo
	fallingComponent = entity->FindComponent<PlayerGravityComponent>();
	if (fallingComponent == NULL)
		return false;

	// Intenta recuperar el componente donde comprobar si está detenido
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	if (inputComponent == NULL)
		return false;

	// Intenta recuperar la hitbox del personaje
	hitboxCollider = dynamic_cast<RectangleBasicCollider*>(inputComponent->colliderComponent->GetCollider());
	if (hitboxCollider == NULL)
		return false;
	// Guarda sus atributos originales
	originalOffsetY = hitboxCollider->offsetY;
	originalHeight = hitboxCollider->height;

	// Registra el timer
	App->time->RegisterTimer(&leapingDownTimer);

	// Carga los efectos de sonidod
	jumpLongSound = App->audio->LoadFx("assets/sounds/player_jump_long.wav");

	return true;
}

bool PlayerJumpComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&leapingDownTimer);

	return true;
}

bool PlayerJumpComponent::OnPreUpdate()
{
	// Comprueba si el timer ha expirado
	if (leapingDownTimer.IsTimerExpired())
		leapingDown = false;

	// Comprueba si el personaje esta mirando hacia arriba
	KeyState keyStateUp = App->input->GetKey(SDL_SCANCODE_W);
	KeyState keyStateDown = App->input->GetKey(SDL_SCANCODE_S);
	bool up = keyStateUp == KEY_DOWN || keyStateUp == KEY_REPEAT;
	bool down = keyStateDown == KEY_DOWN || keyStateDown == KEY_REPEAT;
	if (up && !down)
	{
		lookingUp = !longJumping || fallingComponent->falling;	// No mirará hacia arriba si está haciendo salto largo
		crouch = false;
	}
	else if (!up && down)
	{
		crouch = !jumping && !fallingComponent->falling;	// No se podrá agachar ni saltando ni callendo
		lookingUp = false;
	}
	else
	{
		lookingUp = false;
		crouch = false;
	}

	if (!crouch)
	{
		// Devuelve la hitbox a su tamaño original
		hitboxCollider->offsetY = originalOffsetY;
		hitboxCollider->height = originalHeight;
	}
	else
	{
		// Se agacha, reduciendo la altura de la hitbox a la mitad
		hitboxCollider->offsetY = originalOffsetY / 2;
		hitboxCollider->height = originalHeight / 2;
	}

	// Comprueba si la tecla de saltar (barra espaciadora) fue pulsada
	KeyState keyStateJump = App->input->GetKey(SDL_SCANCODE_SPACE);
	if (keyStateJump == KEY_DOWN || keyStateJump == KEY_REPEAT)
	{
		if (!crouch)
			Jump();
		else
			LeapDown();	// Si está agachado, se baja de la plataforma
	}

	return true;
}

void PlayerJumpComponent::Jump()
{
	// Primero comprueba si la entidad está callendo o saltando
	if (fallingComponent->falling || jumping)
		return;	// No se puede saltar mientras se cae

	if (inputComponent->IsStopped())
		return;	// No se puede saltar si el personaje está detenido

	// Modifica la velocidad vertical de la entidad para hacerla saltar
	fPoint currentSpeed = entity->transform->GetGlobalSpeed();
	float totalJumpSpeed = jumpSpeed * (lookingUp ? longJumpMultiplier : 1.0f);
	entity->transform->SetGlobalSpeed(currentSpeed.x, -totalJumpSpeed);	// Arriba es negativo
	jumping = true;
	longJumping = lookingUp;

	// Reproduce un sonido
	if (jumping && longJumping)
		App->audio->PlayFx(jumpLongSound);
}

void PlayerJumpComponent::LeapDown()
{
	// Primero comprueba si la entidad está agachada
	if (!crouch)
		return;	// No se puede bajar mientras no se está agachado

	if (inputComponent->IsStopped())
		return;	// No se puede bajar si el personaje está detenido

	// Cambia el flag y activa el timer de leaping
	leapingDown = true;
	leapingDownTimer.SetTimer(0.1f);	// Tiempo suficiente para atravesar el collider de la plataforma
}