#include "Player.h"
#include "SpriteRendererComponent.h"
#include "PlayerInputComponent.h"
#include "MovementSimpleComponent.h"
#include "CircleColliderComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "PlayerGravityComponent.h"
#include "PlayerJumpComponent.h"
#include "PlayerAnimator.h"
#include "AnimatorMappingComponent.h"
#include "WeaponTomahawk.h"
#include "PlayerLifeComponent.h"

void Player::OnCreate()
{
	// A�ade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/player_green.png", PlayerAnimator::Create(), -64, -64));
	AddComponent(colliderComponent = new RectangleColliderComponent(28, 47, { WALL, ENEMY, ENEMY_ATTACK, PICKUP }, 0, -24, 0, PLAYER, true));
	AddComponent(new PlayerLifeComponent(colliderComponent, 18, 1.0f, 5.0f, 2.0f));
	AddComponent(new PlayerInputComponent(75.0f, WALL, colliderComponent, 0.1f));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, PLAYER, true));
	AddComponent(new PlayerGravityComponent(500.0f, colliderComponent, 5.0f));
	AddComponent(new PlayerJumpComponent(250.0f, 1.25f));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new AnimatorMappingComponent());
	AddComponent(new WeaponTomahawk());
}

void Player::OnDestroy()
{
	// En principio no hace nada
}