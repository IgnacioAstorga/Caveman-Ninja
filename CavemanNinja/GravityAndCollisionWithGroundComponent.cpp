#include "GravityAndCollisionWithGroundComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "PlayerJumpComponent.h"

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

	falling = true;	// Empieza "callendo", en el primer frame se comprobar� si est� posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de ca�da, da error
}

bool GravityAndCollisionWithGroundComponent::OnUpdate()
{
	// Lo primero, comprueba si la caida se fren� en la frame anterior.
	// Se utiliza para determinar si la entidad est� callendo o no
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	// Mueve a la entidad seg�n la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);

	return true;
}

bool GravityAndCollisionWithGroundComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisi�n es con el suelo
	if (other->GetType() != groundColliderType)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisi�n es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Detecta si est� cayendo. Si no, ignora la colisi�n
	if (entity->transform->GetGlobalSpeed().y <= 0.0f)	// Abajo es positivo, arriba es negativo
		return true;

	// Frena la caida de la entidad
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, 0.0f);
	falling = false;
	jumpComponent->jumping = false;

	// Desplaza la entidad hacia arriba hasta que se encuentre fuera del collider
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other));

	return true;
}
