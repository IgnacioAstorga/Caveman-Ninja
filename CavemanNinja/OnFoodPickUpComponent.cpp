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
		score = 100;
		restoration = 1;
		break;
	case FOOD_MEAT:
		score = 300;
		restoration = 3;
		break;
	case FOOD_BIG:
		score = 500;
		restoration = 5;
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
