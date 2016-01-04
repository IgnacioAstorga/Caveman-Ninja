#include "DieOnPlayerAttackComponent.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleTime.h"

DieOnPlayerAttackComponent::DieOnPlayerAttackComponent(float decayTime, ColliderComponent* colliderComponent, bool start_enabled)
	: Component(start_enabled)
{
	this->decayTime = decayTime;
	this->colliderComponent = colliderComponent;
	this->dead = false;
	this->decaying = false;
}

DieOnPlayerAttackComponent::~DieOnPlayerAttackComponent() {}

bool DieOnPlayerAttackComponent::OnUpdate()
{
	if (!decaying)
		return true;

	decayDuration += App->time->DeltaTime();
	if (decayDuration >= decayTime)
		entity->Destroy();

	return true;
}

bool DieOnPlayerAttackComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Comprueba si es el collider adecuado y si es un ataque del jugador
	if (self != colliderComponent->GetCollider() || other->GetType() != PLAYER_PROJECTILE)
		return true;

	// Desactiva el collider y mata al personaje
	colliderComponent->GetCollider()->Disable();
	dead = true;

	// Lanca al enemigo volando
	entity->transform->SetSpeed(100.0f, -150.0f);
}

void DieOnPlayerAttackComponent::Decay()
{
	// Hace que el enemigo desaparezca
	decaying = true;
	this->decayDuration = 0.0f;
}
