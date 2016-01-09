#include "PlayerGravityComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "PlayerJumpComponent.h"
#include "RectangleBasicCollider.h"

PlayerGravityComponent::PlayerGravityComponent(float gravity, ColliderComponent* colliderComponent, float verticalTolerance)
{
	this->gravity = gravity;
	this->colliderComponent = colliderComponent;
	this->verticalTolerance = verticalTolerance;
}

PlayerGravityComponent::~PlayerGravityComponent()
{
	// En principio no hace nada
}

bool PlayerGravityComponent::OnStart()
{
	// Intenta encontrar el componente de salto de la entidad
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();

	// Carga los efectos de sonido
	landSound = App->audio->LoadFx("assets/sounds/player_jump_land.wav");

	falling = true;	// Empieza "callendo", en el primer frame se comprobar� si est� posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de ca�da, da error
}

bool PlayerGravityComponent::OnUpdate()
{
	// Mueve a la entidad seg�n la gravedad (coordenadas globales)
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);

	// Comprueba si est� callendo
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	// Si est� callendo, comprueba si est� cerca del suelo
	if (falling)
	{
		Collider* checker = new RectangleBasicCollider(NULL, entity->transform, 1.0f, verticalTolerance, 0.0f, verticalTolerance / 2);
		list<Collider*> colliders = App->collisions->CheckCollisions(checker, GROUND);
		if (!colliders.empty())
			// Fuerza la colisi�n
			this->OnCollisionEnter(colliderComponent->GetCollider(), colliders.front());
		RELEASE(checker);
	}

	return true;
}

bool PlayerGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisi�n es con el suelo
	if (other->GetType() != GROUND && other->GetType() != FLOOR)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisi�n es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Si el personaje est� saltando y subiendo, ignora la colisi�n
	if (jumpComponent->jumping && entity->transform->GetLocalSpeed().y < 0.0f)	// Abajo es positivo, arriba es negativo
		return true;

	// Frena la caida de la entidad
	entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	falling = false;
	if (jumpComponent != NULL)
	{
		if (jumpComponent->jumping)
			App->audio->PlayFx(landSound);
		jumpComponent->jumping = false;
		jumpComponent->longJumping = false;
	}

	// Recoloca la entidad
	fPoint newPosition = other->GetExternalPositionFromCoordinates(entity->transform->GetGlobalPosition());
	entity->transform->SetGlobalPosition(newPosition.x, newPosition.y);
	
	return true;
}

bool PlayerGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
