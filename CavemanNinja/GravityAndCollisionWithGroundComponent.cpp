#include "GravityAndCollisionWithGroundComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"
#include "PlayerJumpComponent.h"
#include "RectangleCollider.h"

GravityAndCollisionWithGroundComponent::GravityAndCollisionWithGroundComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float step_size)
{
	this->gravity = gravity;
	this->groundColliderType = groundColliderType;
	this->colliderComponent = colliderComponent;
	this->step_size = step_size;
}

GravityAndCollisionWithGroundComponent::~GravityAndCollisionWithGroundComponent()
{
	// En principio no hace nada
}

bool GravityAndCollisionWithGroundComponent::OnStart()
{
	// Intenta encontrar el componente de salto de la entidad
	jumpComponent = entity->FindComponent<PlayerJumpComponent>();

	falling = true;	// Empieza "callendo", en el primer frame se comprobará si está posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de caída, da error
}

bool GravityAndCollisionWithGroundComponent::OnUpdate()
{
	// Mueve a la entidad según la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	return true;
}

bool GravityAndCollisionWithGroundComponent::OnCollisionEnter(Collider* self, Collider* other)
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
	entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	falling = false;
	jumpComponent->jumping = false;

	// Recoloca la entidad
	int count = 0;
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other) && count++ < 100);
	
	return true;
}

bool GravityAndCollisionWithGroundComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
