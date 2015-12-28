#include "Player.h"
#include "SpriteRendererComponent.h"
#include "PlayerInputComponent.h"
#include "MovementSimpleComponent.h"

void Player::OnCreate()
{
	// Añade las componentes de la entidad
	AddComponent(new SpriteRendererComponent("assets/images/player_green.png", NULL, -14, -47));
	AddComponent(new PlayerInputComponent(30.0f));
	AddComponent(new MovementSimpleComponent());
}

void Player::OnDestroy()
{
	// En principio no hace nada
}