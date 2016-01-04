#include "EnemyGravityComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"
#include "RectangleCollider.h"
#include "DieOnPlayerAttackComponent.h"

EnemyGravityComponent::EnemyGravityComponent(float gravity, ColliderType groundColliderType, ColliderComponent* colliderComponent, float verticalTolerance, float step_size)
{
	this->gravity = gravity;
	this->groundColliderType = groundColliderType;
	this->colliderComponent = colliderComponent;
	this->verticalTolerance = verticalTolerance;
	this->step_size = step_size;
}

EnemyGravityComponent::~EnemyGravityComponent()
{
	// En principio no hace nada
}

bool EnemyGravityComponent::OnStart()
{
	// Intenta encontrar el componente de vida de la entidad
	lifeComponent = entity->FindComponent<DieOnPlayerAttackComponent>();

	falling = true;	// Empieza "callendo", en el primer frame se comprobar� si est� posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de ca�da, da error
}

bool EnemyGravityComponent::OnUpdate()
{
	if (!falling)
	{
		Collider* collisionChecker = new RectangleCollider(NULL, entity->transform, 0, verticalTolerance);
		list<Collider*> collisions = App->collisions->CheckCollisions(collisionChecker, GROUND);
		if (!collisions.empty())
			entity->transform->Move(0, verticalTolerance);
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

bool EnemyGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
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
	if (!lifeComponent->dead)
		entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	else
	{
		entity->transform->SetSpeed(0.0f, 0.0f);	// Si est� muerto lo frena completamente
		lifeComponent->Decay();
		this->Disable();	// Desactiva el componente de gravedad
	}
	falling = false;

	// Recoloca la entidad
	int count = 0;
	do
	{
		entity->transform->SetGlobalPosition(entity->transform->GetGlobalPosition().x, entity->transform->GetGlobalPosition().y - step_size);
	} while (self->CollidesWith(other) && count++ < 100);

	return true;
}

bool EnemyGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
