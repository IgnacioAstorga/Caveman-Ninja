#include "OnFoodPickUpComponent.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "Pickup.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "PlayerLifeComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "ScoreTextEffect.h"
#include "Application.h"
#include "ModuleAudio.h"

#define FOOD_SMALL_SCORE 100
#define FOOD_MEAT_SCORE 300
#define FOOD_BIG_SCORE 500
#define FOOD_SMALL_RESTORATION 1
#define FOOD_MEAT_RESTORATION 3
#define FOOD_BIG_RESTORATION 5

OnFoodPickUpComponent::OnFoodPickUpComponent(PickupType type)
{
	this->type = type;
}

OnFoodPickUpComponent::~OnFoodPickUpComponent()
{
	// En principio no hace nada
}

bool OnFoodPickUpComponent::OnStart()
{
	// Carga el efecto de sonido
	pickupSound = App->audio->LoadFx("assets/sounds/food_pickup.wav");

	return true;
}

bool OnFoodPickUpComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Comprueba que el otro collider sea el jugador
	if (other->GetType() != PLAYER)
		return true;

	// Establece la puntuación y curación adecuadas
	int score;
	int restoration;
	switch (type)
	{
	case FOOD_SMALL:
		score = FOOD_SMALL_SCORE;
		restoration = FOOD_SMALL_RESTORATION;
		break;
	case FOOD_MEAT:
		score = FOOD_MEAT_SCORE;
		restoration = FOOD_MEAT_RESTORATION;
		break;
	case FOOD_BIG:
		score = FOOD_BIG_SCORE;
		restoration = FOOD_BIG_RESTORATION;
		break;
	default:
		return false;
	}

	// Restaura la vida del jugador
	GameController->player->FindComponent<PlayerLifeComponent>()->Heal(restoration);

	// Aumenta la puntuación
	GameController->AddScore(score);

	// Crea el texto especial de los puntos
	fPoint position = entity->transform->GetGlobalPosition();
	Entity* scoreText = new ScoreTextEffect(score, "score_" + entity->name, position.x, position.y);
	scoreText->Instantiate();

	// Destruye el pickup y reproduce el sonido
	App->audio->PlayFx(pickupSound);
	entity->Destroy();

	return true;
}
