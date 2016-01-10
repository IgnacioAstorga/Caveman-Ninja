#include "EnemyGravityComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"
#include "RectangleBasicCollider.h"
#include "DieOnPlayerAttackComponent.h"

EnemyGravityComponent::EnemyGravityComponent(float gravity, ColliderComponent* colliderComponent, float verticalTolerance)
{
	this->gravity = gravity;
	this->colliderComponent = colliderComponent;
	this->verticalTolerance = verticalTolerance;
}

EnemyGravityComponent::~EnemyGravityComponent()
{
	// En principio no hace nada
}

bool EnemyGravityComponent::OnStart()
{
	// Intenta encontrar el componente de vida de la entidad
	lifeComponent = entity->FindComponent<DieOnPlayerAttackComponent>();

	falling = true;	// Empieza "callendo", en el primer frame se comprobará si está posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de caída, da error
}

bool EnemyGravityComponent::OnUpdate()
{
	// Mueve a la entidad según la gravedad (coordenadas globales)
	float newYSpeed = entity->transform->GetGlobalSpeed().y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(entity->transform->GetGlobalSpeed().x, newYSpeed);
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	return true;
}

bool EnemyGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisión es con el suelo
	if (other->GetType() != GROUND && other->GetType() != FLOOR)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisión es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Frena la caida de la entidad
	if (!lifeComponent->dead)
	{
		entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
		falling = false;

		// Recoloca la entidad
		fPoint newPosition = other->GetExternalPositionFromCoordinates(entity->transform->GetGlobalPosition());
		entity->transform->SetGlobalPosition(newPosition.x, newPosition.y);
	}
	else if (falling)
	{
		entity->transform->SetSpeed(0.0f, 0.0f);	// Si está muerto lo frena completamente
		lifeComponent->Decay();
		this->Disable();	// Desactiva el componente de gravedad
	}

	return true;
}

bool EnemyGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
