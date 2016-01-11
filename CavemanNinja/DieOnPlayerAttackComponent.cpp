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
#include "SpawnPickupOnDeathComponent.h"
#include "AIComponent.h"

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
	// Recupera el componente de la IA
	aiComponent = entity->FindComponent<AIComponent>();

	// Registra el timer
	App->time->RegisterTimer(&decayTimer);

	// Carga los efectos de sonido
	hitSound = App->audio->LoadFx("assets/sounds/enemy_hit.wav");
	dieSound = App->audio->LoadFx("assets/sounds/enemy_caveman_die.wav");

	return aiComponent != NULL;
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
	if (self != colliderComponent->GetCollider() || other->GetType() != PLAYER_ATTACK)
		return true;

	// Desactiva el collider, su IA y mata al personaje
	colliderComponent->GetCollider()->Disable();
	aiComponent->Disable();
	dead = true;

	// Crea el efecto especial
	fPoint selfCenter = self->GetCenter();
	fPoint otherCenter = other->GetCenter();
	fPoint damagePosition = selfCenter + (otherCenter - selfCenter) * (1.0f / 2.0f);
	EnemyHitEffect* hitEffect = new EnemyHitEffect("hit_" + entity->name);
	hitEffect->transform->SetGlobalPosition(damagePosition.x, damagePosition.y);
	hitEffect->Instantiate();

	// Lanza al enemigo volando en la dirección adecuada
	if (other->transform->GetGlobalSpeed().x > 0)
		entity->transform->SetSpeed(100.0f, -150.0f);
	else if (other->transform->GetGlobalSpeed().x < 0)
		entity->transform->SetSpeed(-100.0f, -150.0f);
	else if (selfCenter.x > otherCenter.x)
		entity->transform->SetSpeed(100.0f, -150.0f);
	else if (selfCenter.x < otherCenter.x)
		entity->transform->SetSpeed(-100.0f, -150.0f);
	else
		entity->transform->SetSpeed(0.0f, -200.0f);

	// Reproduce los efectos de sonido
	App->audio->PlayFx(hitSound);
	App->audio->PlayFx(dieSound);

	// Da la señal a los componentes que hagan aparecer pickups
	list<SpawnPickupOnDeathComponent*> spawners = entity->FindAllComponents<SpawnPickupOnDeathComponent>();
	for (list<SpawnPickupOnDeathComponent*>::iterator it = spawners.begin(); it != spawners.end(); ++it)
		(*it)->Spawn();

	return true;
}

void DieOnPlayerAttackComponent::Decay()
{
	// Hace que el enemigo desaparezca
	decaying = true;
	decayTimer.SetTimer(decayTime);
}
