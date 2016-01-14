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
#include "SpawnEntityOnDeathComponent.h"
#include "AIComponent.h"
#include "EntityLifetimeComponent.h"

#define BIG_FACTOR 2.0f;

DieOnPlayerAttackComponent::DieOnPlayerAttackComponent(float decayTime, fPoint flySpeed, string dieSoundName, ColliderComponent* colliderComponent, bool start_enabled)
	: Component(start_enabled)
{
	this->decayTime = decayTime;
	this->flySpeed = flySpeed;
	this->dieSoundName = dieSoundName;
	this->colliderComponent = colliderComponent;
	this->dead = false;
	this->decaying = false;
}

DieOnPlayerAttackComponent::~DieOnPlayerAttackComponent() {}

bool DieOnPlayerAttackComponent::OnStart()
{
	// Recupera el componente de la IA
	aiComponent = entity->FindComponent<AIComponent>();

	// Recupera y desactiva el componente de lifetime
	lifetimeComponent = entity->FindComponent<EntityLifetimeComponent>();
	if (lifetimeComponent != NULL)
		lifetimeComponent->Disable();

	// Registra el timer
	App->time->RegisterTimer(&decayTimer);

	// Carga los efectos de sonido
	hitSound = App->audio->LoadFx("assets/sounds/enemy_hit.wav");
	dieSound = App->audio->LoadFx(dieSoundName.c_str());

	return true;
}

bool DieOnPlayerAttackComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&decayTimer);

	return true;
}

bool DieOnPlayerAttackComponent::OnUpdate()
{
	if (!decaying)
		return true;

	if (decayTimer.IsTimerExpired())
		entity->Destroy();

	return true;
}

bool DieOnPlayerAttackComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Comprueba si es el collider adecuado y si es un ataque del jugador
	if (self != colliderComponent->GetCollider() || (other->GetType() != PLAYER_ATTACK && other->GetType() != PLAYER_ATTACK_BIG))
		return true;

	// Mata al personaje
	Die(other->transform, other->GetType() == PLAYER_ATTACK_BIG);

	// Reproduce los efectos de sonido
	App->audio->PlayFx(hitSound);

	// Crea el efecto especial
	fPoint selfCenter = self->GetCenter();
	fPoint otherCenter = other->GetCenter();
	fPoint damagePosition = selfCenter + (otherCenter - selfCenter) * 0.5f;
	EnemyHitEffect* hitEffect = new EnemyHitEffect("hit_" + entity->name, other->GetType() == PLAYER_ATTACK_BIG);
	hitEffect->transform->SetGlobalPosition(damagePosition.x, damagePosition.y);
	hitEffect->Instantiate();

	return true;
}

void DieOnPlayerAttackComponent::Die(Transform* otherTransform, bool big)
{
	if (dead)
		return;

	// Desactiva el collider, su IA y mata al personaje
	if (colliderComponent->GetCollider() != NULL)
		colliderComponent->GetCollider()->Disable();
	if (aiComponent != NULL)
		aiComponent->Disable();
	dead = true;

	fPoint otherSpeed = otherTransform->GetGlobalSpeed();
	fPoint otherPosition = otherTransform->GetGlobalPosition();
	fPoint selfPosition = entity->transform->GetGlobalPosition();

	// Lanza al enemigo volando en la dirección adecuada
	if (otherSpeed.x > 0)
		entity->transform->SetSpeed(flySpeed.x, flySpeed.y);
	else if (otherSpeed.x < 0)
		entity->transform->SetSpeed(-flySpeed.x, flySpeed.y);
	else if (selfPosition.x > otherPosition.x)
		entity->transform->SetSpeed(flySpeed.x, flySpeed.y);
	else if (selfPosition.x < otherPosition.x)
		entity->transform->SetSpeed(-flySpeed.x, flySpeed.y);
	else
		entity->transform->SetSpeed(0.0f, -flySpeed.Norm());
	if (big)
		entity->transform->speed *= BIG_FACTOR;

	// Reproduce los efectos de sonido
	App->audio->PlayFx(dieSound);

	// Da la señal a los componentes que hagan aparecer entidades
	list<SpawnEntityOnDeathComponent*> spawners = entity->FindAllComponents<SpawnEntityOnDeathComponent>();
	for (list<SpawnEntityOnDeathComponent*>::iterator it = spawners.begin(); it != spawners.end(); ++it)
		(*it)->Spawn();

	// Si tiene componente de vida, lo activa
	if (lifetimeComponent != NULL)
		lifetimeComponent->Enable();
}

void DieOnPlayerAttackComponent::Decay()
{
	// Hace que el enemigo desaparezca
	decaying = true;
	decayTimer.SetTimer(decayTime);
}
