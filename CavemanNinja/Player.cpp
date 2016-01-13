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
#include "PlayerArmAnimator.h"
#include "AnimatorMappingComponent.h"
#include "WeaponTomahawk.h"
#include "PlayerLifeComponent.h"

#define LIFE_POINTS 18
#define GRACE_TIME 1.0f
#define HARVEST_PERIOD 5.0f
#define DECAY_TIME 2.0f
#define MOVEMENT_SPEED 75.0f
#define GRAVITY 500.0f
#define JUMP_SPEED 250.0f
#define LONG_JUMP_MULTIPLIER 1.25f
#define MELEE_ATTACK_RADIUS 20.0f
#define MELEE_ATTACK_OFFSET {14, -24}

void Player::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	SpriteRendererComponent* mainRendererComponent;
	SpriteRendererComponent* chargingRendererComponent;
	SpriteRendererComponent* armRendererComponent;
	AddComponent(mainRendererComponent = new SpriteRendererComponent("assets/images/player_green.png", PlayerAnimator::Create(), -64, -128));
	AddComponent(chargingRendererComponent = new SpriteRendererComponent("assets/images/player_green_charging.png", PlayerAnimator::Create(), -64, -128));
	AddComponent(armRendererComponent = new SpriteRendererComponent("assets/images/player_green_arm.png", PlayerArmAnimator::Create(), -48, -48));
	AddComponent(colliderComponent = new RectangleColliderComponent(28, 47, { WALL, ENEMY, ENEMY_ATTACK, PICKUP }, 0, -24, 0, PLAYER, true));
	AddComponent(new PlayerLifeComponent(colliderComponent, LIFE_POINTS, GRACE_TIME, HARVEST_PERIOD, DECAY_TIME));
	AddComponent(new PlayerInputComponent(MOVEMENT_SPEED, colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND, VICTORY }, 0.0f, 0.0f, PLAYER, true));
	AddComponent(new PlayerGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new PlayerJumpComponent(JUMP_SPEED, LONG_JUMP_MULTIPLIER));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new AnimatorMappingComponent(mainRendererComponent, chargingRendererComponent, armRendererComponent));

	// Añade el componente del arma
	vector<int> collisionsTypes;
	collisionsTypes.push_back(ENEMY);
	CircleColliderComponent* meleeComponent;
	AddComponent(meleeComponent = new CircleColliderComponent(MELEE_ATTACK_RADIUS, collisionsTypes, 0.0f, 0.0f, PLAYER_ATTACK, false));
	AddComponent(new WeaponTomahawk(meleeComponent, MELEE_ATTACK_OFFSET));
}

void Player::OnDestroy()
{
	// En principio no hace nada
}