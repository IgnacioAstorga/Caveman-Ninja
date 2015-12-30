#include "PlayerJumpComponent.h"
#include "GravityAndCollisionWithGroundComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleInput.h"

PlayerJumpComponent::PlayerJumpComponent(float jumpSpeed)
{
	this->jumpSpeed = jumpSpeed;
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
	return fallingComponent != NULL;
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

	// Modifica la velocidad vertical de la entidad para hacerla saltar
	fPoint currentSpeed = entity->transform->GetGlobalSpeed();
	entity->transform->SetGlobalSpeed(currentSpeed.x, -jumpSpeed);	// Arriba es negativo
	jumping = true;

	return true;
}
