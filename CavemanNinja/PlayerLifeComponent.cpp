#include "PlayerLifeComponent.h"
#include "ColliderComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "PlayerInputComponent.h"
#include "PlayerGravityComponent.h"
#include "PlayerJumpComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "PlayerHitEffect.h"
#include "PlayerHarvestEffect.h"

#define HARVEST_EFFECT_OFFSET_X 32.0f
#define HARVEST_EFFECT_OFFSET_Y -64.0f
#define BOUNCE_SPEED -100.0f
#define FLY_SPEED_HORIZONTAL 100.0f
#define FLY_SPEED_VERTICAL -100.0f
#define COLLISION_DAMAGE 5
#define DAMAGE_PAUSE_TIME 0.5f
#define EXHAUST_PAUSE_TIME 1.5f
#define EXHAUST_DAMAGE 3

PlayerLifeComponent::PlayerLifeComponent(ColliderComponent* colliderComponent, int lifePoints, float graceTime, float harvestTime, float decayTime, bool harvesting)
{
	this->colliderComponent = colliderComponent;
	this->maxLifePoints = lifePoints;
	this->graceTime = graceTime;
	this->harvestTime = harvestTime;
	this->decayTime = decayTime;
	this->harvesting = harvesting;
}

PlayerLifeComponent::~PlayerLifeComponent()
{
	// En principio no hace nada
}

bool PlayerLifeComponent::OnStart()
{
	// Se establece como el jugador
	Player* player = dynamic_cast<Player*>(entity);
	GameController->player = player;

	// Registra los timers
	App->time->RegisterTimer(&hitTimer);
	App->time->RegisterTimer(&exhaustedTimer);
	App->time->RegisterTimer(&graceTimer);
	App->time->RegisterTimer(&harvestTimer);
	App->time->RegisterTimer(&decayTimer);

	// Inicia el contador de hambre
	harvestTimer.SetTimer(harvestTime);

	// Restablece la vida del jugador
	this->currentLifePoints = maxLifePoints;

	// Recupera los componentes adecuados
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	gravityComponent = entity->FindComponent<PlayerGravityComponent>();

	// Carga los efectos de sonido
	hitSound = App->audio->LoadFx("assets/sounds/player_hit.wav");
	dieSound = App->audio->LoadFx("assets/sounds/player_die.wav");
	exhaustSound = App->audio->LoadFx("assets/sounds/player_exhaust.wav");

	// Establece los valores por defecto
	this->hit = false;
	this->invulnerable = false;
	this->dead = false;
	this->decaying = false;
	this->exhausted = false;

	return true;
}

bool PlayerLifeComponent::OnCleanUp()
{
	// Desregistra los timers
	App->time->UnregisterTimer(&hitTimer);
	App->time->UnregisterTimer(&exhaustedTimer);
	App->time->UnregisterTimer(&graceTimer);
	App->time->UnregisterTimer(&harvestTimer);
	App->time->UnregisterTimer(&decayTimer);

	return true;
}

bool PlayerLifeComponent::OnUpdate()
{
	// Animación de golpeo
	if (hit && hitTimer.IsTimerExpired())
		hit = false;

	// Animación de cansancio
	if (exhausted && exhaustedTimer.IsTimerExpired())
		exhausted = false;

	// Periodo de gracia
	if (invulnerable && graceTimer.IsTimerExpired())
		invulnerable = false;

	// Hambre
	if (harvesting && !dead)
		while (harvestTimer.IsTimerExpired(true))
		{
			Hurt(1, HARVEST);
			if (dead)
			{
				float offsetX;
				if (inputComponent->orientation == FORWARD)
					offsetX = HARVEST_EFFECT_OFFSET_X;
				else
					offsetX = -HARVEST_EFFECT_OFFSET_X;
				PlayerHarvestEffect* effect = new PlayerHarvestEffect("harvest_effect", offsetX, HARVEST_EFFECT_OFFSET_Y);
				effect->Instantiate(entity);
				break;
			}
		}

	// Comienzo del periodo de muerte al llegar al suelo
	if (!hit && !exhausted && dead && gravityComponent->onAir == false)
		Decay();

	// Periodo de muerte
	if (decaying && decayTimer.IsTimerExpired())
		GameController->GameOver();

	// Si el personaje está callendo, su hitbox pasa a ser la de un ataque
	if (gravityComponent->falling && !inputComponent->IsStopped())
		colliderComponent->GetCollider()->type = PLAYER_ATTACK;
	else
		colliderComponent->GetCollider()->type = PLAYER;

	return true;
}

bool PlayerLifeComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Comprueba si es el collider adecuado y si es un ataque del jugador
	if (self != colliderComponent->GetCollider())
		return true;
	if (other->GetType() != ENEMY && other->GetType() != ENEMY_ATTACK && other->GetType() != EGG)
		return true;

	// Si acaba de ser golpeado, aborta
	if (invulnerable)
		return true;

	// Calcula el punto medio entre ambos colliders
	fPoint selfCenter = self->GetCenter();
	fPoint otherCenter = other->GetCenter();
	fPoint damagePosition = selfCenter + (otherCenter - selfCenter) * 0.5f;

	// Si está callendo, rebota. Si no, se hace daño
	if (gravityComponent->falling && other->GetType() != ENEMY_ATTACK)
	{
		entity->transform->SetSpeed(entity->transform->speed.x, BOUNCE_SPEED);
		gravityComponent->jumpComponent->jumping = true;
		gravityComponent->falling = false;
	}
	else if (other->GetType() != EGG)
		// Hace daño al personaje
		TakeDamage(COLLISION_DAMAGE, damagePosition);

	return true;
}

void PlayerLifeComponent::Heal(int amount)
{
	// Restaura la vida del personaje
	currentLifePoints += amount;
	if (currentLifePoints > maxLifePoints)
		currentLifePoints = maxLifePoints;
}

void PlayerLifeComponent::Hurt(int amount, DeathType type, bool stop)
{
	// Resta la vida del personaje
	currentLifePoints -= amount;
	if (currentLifePoints <= 0)
		Die(type, stop);
}

void PlayerLifeComponent::Exhaust()
{
	// Le garantiza inmunidad
	exhausted = true;
	invulnerable = true;
	graceTimer.SetTimer(graceTime);

	// Paraliza al personaje
	inputComponent->Stop(EXHAUST_PAUSE_TIME);
	exhaustedTimer.SetTimer(EXHAUST_PAUSE_TIME);

	// Reproduce el efecto de sonido
	App->audio->PlayFx(exhaustSound);

	// Le resta vida
	entity->transform->speed.x = 0.0f;
	Hurt(EXHAUST_DAMAGE, EXHAUST, true);
}

void PlayerLifeComponent::TakeDamage(int amount, fPoint damagePosition)
{
	// Le garantiza inmunidad
	hit = true;
	invulnerable = true;
	graceTimer.SetTimer(graceTime);

	// Crea el efecto especial
	PlayerHitEffect* hitEffect = new PlayerHitEffect("hit_" + entity->name);
	hitEffect->transform->SetGlobalPosition(damagePosition.x, damagePosition.y);
	hitEffect->Instantiate();

	// Lanza volando al personaje y le paraliza
	inputComponent->Stop(DAMAGE_PAUSE_TIME);
	hitTimer.SetTimer(DAMAGE_PAUSE_TIME);
	if (entity->transform->GetGlobalPosition().x >= damagePosition.x)
		entity->transform->SetSpeed(FLY_SPEED_HORIZONTAL, FLY_SPEED_VERTICAL);
	else
		entity->transform->SetSpeed(-FLY_SPEED_HORIZONTAL, FLY_SPEED_VERTICAL);

	// Simula que el personaje está saltando para poder despegarlo del suelo
	gravityComponent->jumpComponent->jumping = true;

	// Reproduce el efecto de sonido
	App->audio->PlayFx(hitSound);

	// Le resta vida
	Hurt(amount, DAMAGE);
}

void PlayerLifeComponent::Die(DeathType deathType, bool stop)
{
	if (dead)
		return;

	// Mata al personaje
	dead = true;
	harvesting = false;

	// Guarda la causa de la muerte
	deathCause = deathType;

	// Lo detiene y desactiva su collider
	if (stop)
		entity->transform->speed.x = 0.0f;
	inputComponent->Stop(10.0f); // Suficiente tiempo
	colliderComponent->GetCollider()->Disable();
}

void PlayerLifeComponent::Decay()
{
	if (decaying)
		return;

	decaying = true;
	decayTimer.SetTimer(decayTime);
	entity->transform->speed.x = 0.0f;

	// Reproduce el sonido
	App->audio->PlayFx(dieSound);
}
