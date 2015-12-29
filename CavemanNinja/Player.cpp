#include "Player.h"
#include "SpriteRendererComponent.h"
#include "PlayerInputComponent.h"
#include "MovementSimpleComponent.h"
#include "CircleColliderComponent.h"
#include "ColliderTypes.h"
#include "GravityAndCollisionWithGroundComponent.h"

void Player::OnCreate()
{
	falling = new bool(false);

	// Añade las componentes de la entidad
	AddComponent(new SpriteRendererComponent("assets/images/player_green.png", NULL, -14, -47));
	AddComponent(new PlayerInputComponent(30.0f));
	AddComponent(new MovementSimpleComponent());
	CircleColliderComponent* colliderComponent;
	AddComponent(colliderComponent = new CircleColliderComponent(0.0f, 0.0f, 0.0f, PLAYER));
	AddComponent(new GravityAndCollisionWithGroundComponent(100.0f, falling, GROUND, colliderComponent, 0.5f));
}

void Player::OnDestroy()
{
	// En principio no hace nada
}