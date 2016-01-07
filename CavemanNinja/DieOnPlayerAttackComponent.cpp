#include "DieOnPlayerAttackComponent.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"
#include "EnemyHitEffect.h"

DieOnPlayerAttackComponent::DieOnPlayerAttackComponent(float decayTime, ColliderComponent* colliderComponent, bool start_enabled)
	: Component(start_enabled)
{
	this->decayTime = decayTime;
	this->colliderComponent = colliderComponent;
	this->dead = false;
	this->decaying = false;
}

DieOnPlayerAttackComponent::~DieOnPlayerAttackComponent() {}

bool DieOnPlayerAttackComponent::OnStart()
{
	// Carga los efectos de sonido
	hitSound = App->audio->LoadFx("assets/sounds/enemy_hit.wav");
	dieSound = App->audio->LoadFx("assets/sounds/enemy_caveman_die.wav");

	return true;
}

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
	if (self != colliderComponent->GetCollider() || other->GetType() != PLAYER_ATTACK)
		return true;

	// Desactiva el collider y mata al personaje
	colliderComponent->GetCollider()->Disable();
	dead = true;

	// Crea el efecto especial
	EnemyHitEffect* hitEffect = new EnemyHitEffect("hit_" + entity->name);
	fPoint otherPosition = other->transform->GetGlobalPosition();
	hitEffect->transform->SetGlobalPosition(otherPosition.x, otherPosition.y);
	hitEffect->Instantiate();

	// Lanca al enemigo volando en la dirección adecuada
	if (other->transform->GetGlobalSpeed().x > 0)
		entity->transform->SetSpeed(100.0f, -150.0f);
	else if (other->transform->GetGlobalSpeed().x < 0)
		entity->transform->SetSpeed(-100.0f, -150.0f);
	else
		entity->transform->SetSpeed(0.0f, -200.0f);

	// Reproduce los efectos de sonido
	App->audio->PlayFx(hitSound);
	App->audio->PlayFx(dieSound);

	return true;
}

void DieOnPlayerAttackComponent::Decay()
{
	// Hace que el enemigo desaparezca
	decaying = true;
	this->decayDuration = 0.0f;
}
