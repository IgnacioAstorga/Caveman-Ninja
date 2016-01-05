#include "WeaponGravityComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"

WeaponGravityComponent::WeaponGravityComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float step_size)
{
	this->gravity = gravity;
	this->groundColliderType = groundColliderType;
	this->colliderComponent = colliderComponent;
	this->step_size = step_size;
}

WeaponGravityComponent::~WeaponGravityComponent()
{
	// En principio no hace nada
}

bool WeaponGravityComponent::OnStart()
{
	falling = true;	// Empieza "callendo", en el primer frame se comprobará si está posado o no
	onGround = false;

	// Recupera el componente de tiempo de vida
	lifespanComponent = entity->FindComponent<WeaponLifespanComponent>();
	if (lifespanComponent == NULL)
		return false;

	return colliderComponent != NULL;	// Si no ha especificado collider
}

bool WeaponGravityComponent::OnUpdate()
{
	// Mueve a la entidad según la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	return true;
}

bool WeaponGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisión es con el suelo
	if (other->GetType() != groundColliderType)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisión es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Ahora detecta si está cayendo o posado. Si no, ignora la colisión
	if (entity->transform->GetLocalSpeed().y < 0.0f)	// Abajo es positivo, arriba es negativo
		return true;

	// Frena la caida de la entidad
	entity->transform->SetSpeed(0.0f, 0.0f);
	falling = false;
	onGround = true;

	// Desactiva este componente y el collider
	this->Disable();
	colliderComponent->GetCollider()->Disable();
	lifespanComponent->Reset(0.2f);

	// Recoloca la entidad
	int count = 0;
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other) && count++ < 100);

	return true;
}

bool WeaponGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
