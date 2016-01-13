#include "RollingBallGravityComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"
#include "RectangleBasicCollider.h"
#include "DieOnPlayerAttackComponent.h"

RollingBallGravityComponent::RollingBallGravityComponent(float gravity, float friction, ColliderComponent* colliderComponent)
{
	this->gravity = gravity;
	this->friction = friction;
	this->colliderComponent = colliderComponent;
}

RollingBallGravityComponent::~RollingBallGravityComponent()
{
	// En principio no hace nada
}

bool RollingBallGravityComponent::OnStart()
{
	// Intenta encontrar el componente de vida de la entidad
	lifeComponent = entity->FindComponent<DieOnPlayerAttackComponent>();

	falling = true;	// Empieza "callendo", en el primer frame se comprobará si está posado o no
	return colliderComponent != NULL;	// Si no ha especificado collider o flag de caída, da error
}

bool RollingBallGravityComponent::OnPreUpdate()
{
	// Guarda la posición de la entidad, antes de ser modificada
	lastPosition = entity->transform->GetGlobalPosition();

	return true;
}

bool RollingBallGravityComponent::OnUpdate()
{
	// Mueve a la entidad según la gravedad (coordenadas globales)
	fPoint speed = entity->transform->GetGlobalSpeed();
	float newYSpeed = speed.y + gravity * App->time->DeltaTime();
	entity->transform->SetGlobalSpeed(speed.x, newYSpeed);

	// Determina si está callendo
	if (entity->transform->GetGlobalSpeed().y > 0)
		falling = true;

	return true;
}

bool RollingBallGravityComponent::OnCollisionEnter(Collider* self, Collider* other)
{
	// Primero, detecta si la colisión es con el suelo
	if (other->GetType() != GROUND && other->GetType() != FLOOR)
		return true;

	// Segundo, detecta si el collider que ha realizado la colisión es el correcto
	if (self != colliderComponent->GetCollider())
		return true;

	// Comprueba si está muerto y ha caido al suelo
	//if (lifeComponent->dead && falling)
	if (false)
	{
		entity->transform->SetSpeed(0.0f, 0.0f);
		lifeComponent->Decay();
		this->Disable();	// Desactiva el componente de gravedad
		return true;
	}

	// Frena la caida de la entidad
	entity->transform->SetSpeed(entity->transform->GetLocalSpeed().x, 0.0f);
	falling = false;

	// Recoloca la entidad
	fPoint newPosition = other->GetExternalPositionFromCoordinates(entity->transform->GetGlobalPosition());
	entity->transform->SetGlobalPosition(newPosition.x, newPosition.y);

	// Calcula la velocidad convertida por la pendiente
	fPoint translation = newPosition - lastPosition;
	if (translation.x != 0 || translation.y != 0)
		lastFrameVelocity = fPoint(0.0f, gravity).ProjectionOn(translation);
	entity->transform->Accelerate(lastFrameVelocity * App->time->DeltaTime() * friction);

	return true;
}

bool RollingBallGravityComponent::OnCollisionStay(Collider * self, Collider * other)
{
	return OnCollisionEnter(self, other);
}
