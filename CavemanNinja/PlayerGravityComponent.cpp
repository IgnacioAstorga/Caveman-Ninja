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
#include "RectangleCollider.h"

PlayerGravityComponent::PlayerGravityComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float verticalTolerance, float step_size)
{
	this->gravity = gravity;
	this->groundColliderType = groundColliderType;
	this->colliderComponent = colliderComponent;
	this->verticalTolerance = verticalTolerance;
	this->step_size = step_size;
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
	onGround = false;
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de ca�da, da error
}

bool PlayerGravityComponent::OnUpdate()
{
	onGround = false;
	if (!falling && (jumpComponent == NULL || !jumpComponent->jumping))
	{
		Collider* collisionChecker = new RectangleCollider(NULL, entity->transform, 0, verticalTolerance);
		list<Collider*> collisions = App->collisions->CheckCollisions(collisionChecker, GROUND);
		if (!collisions.empty())
		{
			entity->transform->Move(0, verticalTolerance);
			onGround = true;
		}
		RELEASE(collisionChecker);
	}

	// Mueve a la entidad seg�n la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	return true;
}

bool PlayerGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisi�n es con el suelo
	if (other->GetType() != groundColliderType && other->GetType() != FLOOR)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisi�n es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Ahora detecta si est� cayendo o posado. Si no, ignora la colisi�n
	if (entity->transform->GetLocalSpeed().y < 0.0f)	// Abajo es positivo, arriba es negativo
		return true;

	// Frena la caida de la entidad
	entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	falling = false;
	onGround = true;
	if (jumpComponent != NULL)
	{
		if (jumpComponent->jumping)
			App->audio->PlayFx(landSound);
		jumpComponent->jumping = false;
		jumpComponent->longJumping = false;
	}

	// Recoloca la entidad
	int count = 0;
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other) && count++ < 100);
	
	return true;
}

bool PlayerGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}