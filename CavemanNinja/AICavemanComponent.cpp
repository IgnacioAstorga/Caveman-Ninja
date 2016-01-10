#include "AICavemanComponent.h"
#include "Entity.h"
#include "DieOnPlayerAttackComponent.h"
#include "Application.h"
#include "ModuleTime.h"
#include "ModuleAudio.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "ColliderComponent.h"
#include "EntityLifetimeComponent.h"
#include "CircleColliderComponent.h"

#define LEFT -1
#define RIGHT 1

#define WALK_SPEED 25.0f
#define CHARGE_SPEED 100.0f
#define RUN_SPEED 300.0f

#define CHARGE_START_DISTANCE 100.0f
#define CHARGE_STOP_DISTANCE 300.0f
#define ATTACK_DISTANCE_HORIZONTAL 40.0f
#define ATTACK_DISTANCE_VERTICAL 20.0f

#define ATTACK_OFFSET_HORIZONTAL 15.0f
#define ATTACK_OFFSET_VERTICAL -23.0f

#define WAIT_FOR_SEARCH 5.0f
#define TIME_SEARCHING 1.5f
#define ATTACK_DURATION 0.5f
#define RUN_START_DELAY 0.5f

AICavemanComponent::AICavemanComponent(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent, float frecuency)
{
	this->attackComponent = attackComponent;
	this->hitboxComponent = hitboxComponent;
	SetFrecuency(frecuency);
}

AICavemanComponent::~AICavemanComponent()
{
	// No hace nada
}

bool AICavemanComponent::OnStart()
{
	// Registra el timer
	App->time->RegisterTimer(&timer);

	// Establece el estado inicial de la IA
	SetState(IDLE);
	timeSinceLastTick = 0;

	// Desactiva el collider de ataque
	attackComponent->Disable();

	// Busca el componente de lifetime y lo desactiva
	lifetimeComponent = entity->FindComponent<EntityLifetimeComponent>();
	lifetimeComponent->Disable();

	// Carga los efectos de sonido
	runStartSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run_start.wav");
	runSound = App->audio->LoadFx("assets/sounds/enemy_caveman_run.wav");
	
	// Comprueba que los componentes estén definidos
	return attackComponent != NULL && hitboxComponent != NULL && lifetimeComponent != NULL;
}

bool AICavemanComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&timer);

	return true;
}

bool AICavemanComponent::OnUpdate()
{
	timeSinceLastTick += App->time->DeltaTime();
	while (timeSinceLastTick >= timeBeetwenTicks)
	{
		timeSinceLastTick -= timeBeetwenTicks;
		TickIA();
	}
	return true;
}

void AICavemanComponent::SetState(IACavemanState state)
{
	switch (state)
	{
	case IDLE:
		// Inicia el contador para buscar
		timer.SetTimer(WAIT_FOR_SEARCH);
		// Establece la orientación hacia el jugador
		if (entity->transform->GetGlobalPosition().x >= GameController->player->transform->GetGlobalPosition().x)
			orientation = LEFT;
		else
			orientation = RIGHT;
		// Cambia el estado
		this->state = state;
		break;
	case SEARCH:
		// Inicia el contador para dejar de buscar
		timer.SetTimer(TIME_SEARCHING);
		// Cambia el estado
		this->state = state;
		break;
	case CHARGE:
		// Establece la orientación hacia el jugador
		if (entity->transform->GetGlobalPosition().x >= GameController->player->transform->GetGlobalPosition().x)
			orientation = LEFT;
		else
			orientation = RIGHT;
		// Cambia el estado
		this->state = state;
		break;
	case ATTACK:
		// Inicia el contador que indica la duración del ataque
		timer.SetTimer(ATTACK_DURATION);
		// Cambia el estado
		this->state = state;
		break;
	case START_RUN:
		// Inicia el contador que indica la duración del breve periodo antes de huir
		timer.SetTimer(RUN_START_DELAY);
		// Cambia el estado
		this->state = state;
		// Reproduce el sonido
		App->audio->PlayFx(runStartSound);
		break;
	case RUN:
		// Cambia el estado
		this->state = state;
		// Reproduce el sonido
		App->audio->PlayFx(runSound);
		break;
	}
}

IACavemanState AICavemanComponent::GetState()
{
	return state;
}

int AICavemanComponent::GetOrientation()
{
	return orientation;
}

void AICavemanComponent::SetFrecuency(float frecuency, bool reset)
{
	timeBeetwenTicks = 1.0f / frecuency;
	if (reset)
		timeSinceLastTick = 0.0f;
}

void AICavemanComponent::TickIA()
{
	switch (state)
	{
	case IDLE:
		TickIDLE();
		break;
	case SEARCH:
		TickSEARCH();
		break;
	case CHARGE:
		TickCHARGE();
		break;
	case ATTACK:
		TickATTACK();
		break;
	case START_RUN:
		TickSTART_RUN();
		break;
	case RUN:
		TickRUN();
		break;
	}
}

void AICavemanComponent::TickIDLE()
{
	// Hace caminar el personaje en la dirección adecuada
	entity->transform->speed.x = orientation * WALK_SPEED;

	// Una vez cada cierto tiempo, se detiene para buscar al jugador
	if (timer.IsTimerExpired())
		SetState(SEARCH);
}

void AICavemanComponent::TickSEARCH()
{
	// Detiene al personaje mientras busca
	entity->transform->speed.x = 0.0f;

	// Si encuentra al jugador, carga hacia él
	if (abs(entity->transform->GetGlobalPosition().x - GameController->player->transform->GetGlobalPosition().x) <= CHARGE_START_DISTANCE)
		SetState(CHARGE);

	// Al terminar, si no encontró al jugador, vuelve a caminar hacia él
	else if (timer.IsTimerExpired())
		SetState(IDLE);
}

void AICavemanComponent::TickCHARGE()
{
	// Corre en la dirección del jugador
	entity->transform->speed.x = orientation * CHARGE_SPEED;

	fPoint thisPosition = entity->transform->GetGlobalPosition();
	fPoint playerPosition = GameController->player->transform->GetGlobalPosition();

	// Si se acerca suficiente al jugador, ataca
	if ((abs(thisPosition.x - playerPosition.x) <= ATTACK_DISTANCE_HORIZONTAL) &&
		(abs(thisPosition.y - playerPosition.y) <= ATTACK_DISTANCE_VERTICAL))
		SetState(ATTACK);

	// Si se aleja demasiado del jugador, vuelve a buscarlo
	else if (abs(entity->transform->GetGlobalPosition().x - GameController->player->transform->GetGlobalPosition().x) >= CHARGE_STOP_DISTANCE)
		SetState(SEARCH);
}

void AICavemanComponent::TickATTACK()
{
	// Detiene al personaje mientras ataca
	entity->transform->speed.x = 0.0f;

	// Activa el collider de ataque y establece su offset
	if (!attackComponent->IsEnabled())
	{
		attackComponent->Enable();
		attackComponent->SetOffset(orientation * ATTACK_OFFSET_HORIZONTAL, ATTACK_OFFSET_VERTICAL);
	}

	// Si ha terminado de atacar, empieza a huir
	if (timer.IsTimerExpired())
	{
		// Desactiva el collider
		attackComponent->Disable();

		// Cambia de estado
		SetState(START_RUN);
	}
}

void AICavemanComponent::TickSTART_RUN()
{
	// Detiene al personaje mientras empieza a correr
	entity->transform->speed.x = 0.0f;

	// Cuando esté listo, huye
	if (timer.IsTimerExpired())
		SetState(RUN);
}

void AICavemanComponent::TickRUN()
{
	// Huye en dirección opuesta
	orientation = -1 * orientation;
	entity->transform->speed.x = orientation * RUN_SPEED;

	// Desactiva la hitbox del personaje
	hitboxComponent->Disable();

	// Activa el componente de desaparición del personaje
	lifetimeComponent->Enable();

	// Desactiva el componente de la IA (es decir, este)
	this->Disable();
}
