#include "Player.h"
#include "SpriteRendererComponent.h"
#include "PlayerInputComponent.h"
#include "MovementSimpleComponent.h"
#include "CircleColliderComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "GravityAndCollisionWithGroundComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerAnimator.h"
#include "AnimatorMappingComponent.h"

void Player::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/player_green.png", PlayerAnimator::Create(), -32, -64));
	AddComponent(colliderComponent = new RectangleColliderComponent(28, 47, 0, -24, 0, NONE));
	AddComponent(new PlayerInputComponent(100.0f, WALL, colliderComponent, 0.1f));
	AddComponent(colliderComponent = new CircleColliderComponent(0.0f, 0.0f, 0.0f, PLAYER, true));
	AddComponent(new GravityAndCollisionWithGroundComponent(500.0f, GROUND, colliderComponent, 0.1f));
	AddComponent(new PlayerJumpComponent(300.0f, 1.25f));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new AnimatorMappingComponent());
}

void Player::OnDestroy()
{
	// En principio no hace nada
}