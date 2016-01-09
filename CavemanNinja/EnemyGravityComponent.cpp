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

EnemyGravityComponent::EnemyGravityComponent(float gravity, ColliderComponent* colliderComponent, float verticalTolerance, float step_size)
{
	this->gravity = gravity;
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

	falling = true;	// Empieza "callendo", en el primer frame se comprobará si está posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de caída, da error
}

bool EnemyGravityComponent::OnUpdate()
{
	if (!falling)
	{
		Collider* collisionChecker = new RectangleBasicCollider(NULL, entity->transform, 0, verticalTolerance);
		list<Collider*> collisions = App->collisions->CheckCollisions(collisionChecker, GROUND);
		if (!collisions.empty())
			entity->transform->Move(0, verticalTolerance);
		RELEASE(collisionChecker);
	}

	// Mueve a la entidad según la gravedad (coordenadas globales)
	// Suma la gravedad a la velocidad de la entidad
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
		entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	else
	{
		entity->transform->SetSpeed(0.0f, 0.0f);	// Si está muerto lo frena completamente
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
