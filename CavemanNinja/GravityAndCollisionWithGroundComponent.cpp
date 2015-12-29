#include "GravityAndCollisionWithGroundComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"

GravityAndCollisionWithGroundComponent::GravityAndCollisionWithGroundComponent(float gravity, bool* falling, ColliderType groundColliderType, ColliderComponent* colliderComponent, float step_size)
{
	this->gravity = gravity;
	this->falling = falling;
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
	return colliderComponent != NULL && falling != NULL;	// Si no ha especificado collider o flag de caída, da error
}

bool GravityAndCollisionWithGroundComponent::OnUpdate()
{
	// Lo primero, comprueba si la caida se frenó en la frame anterior.
	// Se utiliza para determinar si la entidad está callendo o no
	if (entity->transform->GetGlobalSpeed().y > 0)
		*falling = true;

	// Mueve a la entidad según la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);

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

	// Detecta si está cayendo. Si no, ignora la colisión
	if (entity->transform->GetGlobalSpeed().y <= 0.0f)	// Abajo es positivo, arriba es negativo
		return true;

	// Frena la caida de la entidad
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, 0.0f);

	// Desplaza la entidad hacia arriba hasta que se encuentre fuera del collider
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other));

	return true;
}
