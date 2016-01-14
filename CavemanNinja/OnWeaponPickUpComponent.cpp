#include "OnWeaponPickUpComponent.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "WeaponPickup.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "Entity.h"
#include "Transform.h"
#include "ScoreTextEffect.h"
#include "Application.h"
#include "ModuleAudio.h"

#define WEAPON_SCORE 1000

OnWeaponPickUpComponent::OnWeaponPickUpComponent(WeaponPickupType type)
{
	this->type = type;
}

OnWeaponPickUpComponent::~OnWeaponPickUpComponent()
{
	// En principio no hace nada
}

bool OnWeaponPickUpComponent::OnStart()
{
	// Carga el efecto de sonido
	pickupSound = App->audio->LoadFx("assets/sounds/weapon_pickup.wav");

	return true;
}

bool OnWeaponPickUpComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	// Comprueba que el otro collider sea el jugador
	if (other->GetType() != PLAYER)
		return true;

	// Establece el arma que se le dará al jugador
	GameController->player->SetWeapon(type);

	// Aumenta la puntuación
	GameController->AddScore(WEAPON_SCORE);

	// Crea el texto especial de los puntos
	fPoint position = entity->transform->GetGlobalPosition();
	Entity* scoreText = new ScoreTextEffect(WEAPON_SCORE, "score_" + entity->name, position.x, position.y);
	scoreText->Instantiate();

	// Destruye el pickup y reproduce el sonido
	App->audio->PlayFx(pickupSound);
	entity->Destroy();

	return true;
}
