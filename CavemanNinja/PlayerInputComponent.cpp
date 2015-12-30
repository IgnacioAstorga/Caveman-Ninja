#include "PlayerInputComponent.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Entity.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "Collider.h"
#include "SDL.h"

PlayerInputComponent::PlayerInputComponent(float speed, ColliderType colliderType, ColliderComponent* colliderComponent, float step_size)
{
	this->speed = speed;
	this->wallColliderType = colliderType;
	this->colliderComponent = colliderComponent;
	this->step_size = step_size;
}

PlayerInputComponent::~PlayerInputComponent() {}

bool PlayerInputComponent::OnPreUpdate()
{
	// Lee las pulsaciones de las teclas A y D y las mapea a la velocidad
	KeyState left = App->input->GetKey(SDL_SCANCODE_A);
	KeyState right = App->input->GetKey(SDL_SCANCODE_D);
	bool leftPressed = left == KEY_DOWN || left == KEY_REPEAT;
	bool rightPressed = right == KEY_DOWN || right == KEY_REPEAT;

	if (leftPressed && !rightPressed)
		entity->transform->speed.x = -speed;
	else if (!leftPressed && rightPressed)
		entity->transform->speed.x = speed;
	else
		entity->transform->speed.x = 0.0f;

	return true;
}

bool PlayerInputComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Primero, detecta si la colisión es con una pared
	if (other->GetType() != wallColliderType)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisión es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Ahora detecta si está moviéndose en la dirección de la pared. Si no, ignora la colisión
	fPoint wallRelativeDirection = other->transform->GetGlobalPosition() - self->transform->GetGlobalPosition();
	if (wallRelativeDirection.x * entity->transform->GetGlobalSpeed().x <= 0)	// Si dan menor que 0, tienen signo distinto, luego son direcciones opuestas
		return true;

	// Frena el movimiento del personaje
	entity->transform->SetSpeed(0.0f, entity->transform->GetLocalSpeed().y);

	// Recoloca la entidad
	int count = 0;
	float stepDirection = 0;
	if (wallRelativeDirection.x < 0)
		stepDirection = -1;
	else if (wallRelativeDirection.x > 0)
		stepDirection = 1;
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x - stepDirection * step_size, entity->transform->GetGlobalPosition().y);
	} while (self->CollidesWith(other) && count++ < 100);

	return true;
}

bool PlayerInputComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
