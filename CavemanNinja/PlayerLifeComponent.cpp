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

PlayerLifeComponent::PlayerLifeComponent(ColliderComponent* colliderComponent, int lifePoints, float graceTime, float harvestTime, float decayTime, bool harvesting)
{
	this->colliderComponent = colliderComponent;
	this->maxLifePoints = lifePoints;
	this->graceTime = graceTime;
	this->harvestTime = harvestTime;
	this->decayTime = decayTime;
	this->harvesting = harvesting;
	this->hit = false;
	this->invulnerable = false;
	this->dead = false;
	this->decaying = false;
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

	// Inicia el contador de hambre
	harvestDuration = 0.0f;

	// Restablece la vida del jugador
	this->currentLifePoints = maxLifePoints;

	// Recupera los componentes adecuados
	inputComponent = entity->FindComponent<PlayerInputComponent>();
	gravityComponent = entity->FindComponent<PlayerGravityComponent>();

	// Carga el efecto de sonido al ser golpeado
	hitSound = App->audio->LoadFx("assets/sounds/player_hit.wav");

	return true;
}

bool PlayerLifeComponent::OnUpdate()
{
	// Animación de golpeo
	if (hit && !inputComponent->IsStopped())
		hit = false;

	// Periodo de gracia
	if (invulnerable)
	{
		graceDuration += App->time->DeltaTime();
		if (graceDuration >= graceTime)
			invulnerable = false;
	}

	// Hambre
	if (harvesting)
	{
		harvestDuration += App->time->DeltaTime();
		while (harvestDuration >= harvestTime)
		{
			harvestDuration -= harvestTime;
			currentLifePoints -= 1;
			if (currentLifePoints <= 0)
			{
				Die(HARVEST);
				float offsetX;
				if (inputComponent->orientation == FORWARD)
					offsetX = 32;
				else
					offsetX = -32;
				PlayerHarvestEffect* effect = new PlayerHarvestEffect("harvest_effect", offsetX, -64);
				effect->Instantiate(entity);
				break;
			}
		}
	}

	// Comienzo del periodo de muerte al llegar al suelo
	if (dead && gravityComponent->jumpComponent->jumping == false)
		Decay();

	// Periodo de muerte
	if (decaying)
	{
		decayDuration += App->time->DeltaTime();
		if (decayDuration >= decayTime)
			GameController->GameOver();
	}

	// Si el personaje está callendo, su hitbox pasa a ser la de un ataque
	if (gravityComponent->falling)
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
	if (other->GetType() != ENEMY && other->GetType() != ENEMY_ATTACK)
		return true;

	// Si acaba de ser golpeado, aborta
	if (invulnerable)
		return true;

	// Calcula el punto medio entre ambos colliders
	fPoint selfCenter = self->GetCenter();
	fPoint otherCenter = other->GetCenter();
	fPoint damagePosition = selfCenter + (otherCenter - selfCenter) * (1.0f / 2.0f);

	// Si está callendo, rebota. Si no, se hace daño
	if (gravityComponent->falling)
		entity->transform->SetSpeed(entity->transform->speed.x, -100.0f);
	else
		// Hace daño al personaje
		TakeDamage(5, damagePosition);	// 5 es el daño por colisión con enemigo

	return true;
}

void PlayerLifeComponent::Heal(int amount)
{
	// Restaura la vida del personaje
	currentLifePoints += amount;
	if (currentLifePoints > maxLifePoints)
		currentLifePoints = maxLifePoints;
}

void PlayerLifeComponent::TakeDamage(int amount, fPoint damagePosition)
{
	// Le garantiza inmunidad
	hit = true;
	invulnerable = true;
	graceDuration = 0.0f;

	// Crea el efecto especial
	PlayerHitEffect* hitEffect = new PlayerHitEffect("hit_" + entity->name);
	hitEffect->transform->SetGlobalPosition(damagePosition.x, damagePosition.y);
	hitEffect->Instantiate();

	// Lanza volando al personaje y le paraliza
	inputComponent->Stop(0.5f);
	if (entity->transform->GetGlobalPosition().x >= damagePosition.x)
		entity->transform->SetSpeed(100.0f, -100.0f);
	else
		entity->transform->SetSpeed(-100.0f, -100.0f);

	// Simula que el personaje está saltando para poder despegarlo del suelo
	gravityComponent->jumpComponent->jumping = true;

	// Reproduce el efecto de sonido
	App->audio->PlayFx(hitSound);

	// Le resta vida
	currentLifePoints -= amount;
	if (currentLifePoints <= 0)
		Die(DAMAGE, false);
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
	decayDuration = 0.0f;
	entity->transform->speed.x = 0.0f;
}
