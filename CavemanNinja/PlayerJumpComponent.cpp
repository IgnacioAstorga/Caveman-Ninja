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

	// Intenta recuperar el componente donde comprobar si se est� callendo
	fallingComponent = entity->FindComponent<PlayerGravityComponent>();
	if (fallingComponent == NULL)
		return false;

	// Intenta recuperar el componente donde comprobar si est� detenido
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

	// Carga los efectos de sonido
	jumpLongSound = App->audio->LoadFx("assets/sounds/player_jump_long.wav");

	return true;
}

bool PlayerJumpComponent::OnPreUpdate()
{
	// Comprueba si el personaje esta mirando hacia arriba
	KeyState keyStateUp = App->input->GetKey(SDL_SCANCODE_W);
	KeyState keyStateDown = App->input->GetKey(SDL_SCANCODE_S);
	bool up = keyStateUp == KEY_DOWN || keyStateUp == KEY_REPEAT;
	bool down = keyStateDown == KEY_DOWN || keyStateDown == KEY_REPEAT;
	if (up && !down)
	{
		lookingUp = !longJumping || fallingComponent->falling;	// No mirar� hacia arriba si est� haciendo salto largo
		crouch = false;
	}
	else if (!up && down)
	{
		crouch = !jumping && !fallingComponent->falling;	// No se podr� agachar ni saltando ni callendo
		lookingUp = false;
	}
	else
	{
		lookingUp = false;
		crouch = false;
	}

	if (!crouch)
	{
		// Devuelve la hitbox a su tama�o original
		hitboxCollider->offsetY = originalOffsetY;
		hitboxCollider->height = originalHeight;

		// Comprueba si la tecla de saltar (barra espaciadora) fue pulsada
		KeyState keyStateJump = App->input->GetKey(SDL_SCANCODE_SPACE);
		if (keyStateJump == KEY_DOWN || keyStateJump == KEY_REPEAT)
			Jump();
	}
	else
	{
		// Se agacha, reduciendo la altura de la hitbox a la mitad
		hitboxCollider->offsetY = originalOffsetY / 2;
		hitboxCollider->height = originalHeight / 2;
	}

	return true;
}

void PlayerJumpComponent::Jump()
{
	// Primero comprueba si la entidad est� callendo o saltando
	if (fallingComponent->falling || jumping)
		return;	// No se puede saltar mientras se cae

	if (inputComponent->IsStopped())
		return;	// No se puede saltar si el personaje est� detenido

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