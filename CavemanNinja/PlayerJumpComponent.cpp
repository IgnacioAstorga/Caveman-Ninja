#include "PlayerJumpComponent.h"
#include "GravityAndCollisionWithGroundComponent.h"
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

	// Intenta recuperar el componente donde comprobar si se está callendo
	fallingComponent = entity->FindComponent<GravityAndCollisionWithGroundComponent>();
	if (fallingComponent == NULL)
		return false;

	// Carga los efectos de sonido
	jumpSound = App->audio->LoadFx("assets/sounds/player_jump.wav");
	jumpLongSound = App->audio->LoadFx("assets/sounds/player_jump_long.wav");

	return true;
}

bool PlayerJumpComponent::OnPreUpdate()
{
	// Primero comprueba si ela entidad está callendo o saltando
	if (fallingComponent->falling || jumping)
		return true;	// No se puede saltar mientras se cae

	// Comprueba si la tecla de saltar (barra espaciadora) fue pulsada
	KeyState keyState = App->input->GetKey(SDL_SCANCODE_SPACE);
	if (keyState != KEY_DOWN && keyState != KEY_REPEAT)
		return true;

	// Comprueba si el salto es alto o no
	keyState = App->input->GetKey(SDL_SCANCODE_W);
	bool longJump = keyState == KEY_DOWN || keyState == KEY_REPEAT;

	// Modifica la velocidad vertical de la entidad para hacerla saltar
	fPoint currentSpeed = entity->transform->GetGlobalSpeed();
	float totalJumpSpeed = jumpSpeed * (longJump ? longJumpMultiplier : 1.0f);
	entity->transform->SetGlobalSpeed(currentSpeed.x, -totalJumpSpeed);	// Arriba es negativo
	jumping = true;
	longJumping = longJump;

	// Reproduce un sonido
	if (jumping)
		if (longJumping)
			App->audio->PlayFx(jumpLongSound);
		else
			App->audio->PlayFx(jumpSound);

	return true;
}
