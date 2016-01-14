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
#include "PlayerLifeComponent.h"
#include "WeaponPickup.h"

#include "WeaponTomahawk.h"
#include "WeaponFang.h"
#include "WeaponBoomerang.h"

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
	AddComponent(colliderComponent = new RectangleColliderComponent(28, 47, { WALL, ENEMY, ENEMY_ATTACK, PICKUP, EGG }, 0, -24, 0, PLAYER, true));
	AddComponent(new PlayerLifeComponent(colliderComponent, LIFE_POINTS, GRACE_TIME, HARVEST_PERIOD, DECAY_TIME));
	AddComponent(new PlayerInputComponent(MOVEMENT_SPEED, colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND, VICTORY }, 0.0f, 0.0f, PLAYER, true));
	AddComponent(new PlayerGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new PlayerJumpComponent(JUMP_SPEED, LONG_JUMP_MULTIPLIER));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new AnimatorMappingComponent(mainRendererComponent, chargingRendererComponent, armRendererComponent));
	AddComponent(meleeComponent = new CircleColliderComponent(MELEE_ATTACK_RADIUS, { ENEMY, EGG }, 0.0f, 0.0f, PLAYER_ATTACK, false));

	SetWeapon(WEAPON_TOMAHAWK);	// Añade el arma inicial
}

void Player::OnDestroy()
{
	// En principio no hace nada
}

void Player::SetWeapon(WeaponPickupType newWeaponType)
{
	// Determina el nuevo arma
	WeaponComponent* newWeapon;
	switch (newWeaponType)
	{
	case WEAPON_TOMAHAWK:
		newWeapon = new WeaponTomahawk(meleeComponent, MELEE_ATTACK_OFFSET);
		break;
	case WEAPON_FANG:
		newWeapon = new WeaponFang(meleeComponent, MELEE_ATTACK_OFFSET);
		break;
	case WEAPON_BOOMERANG:
		newWeapon = new WeaponBoomerang(meleeComponent, MELEE_ATTACK_OFFSET);
		break;
	default:
		return;
	}

	// Recupera su arma actual
	WeaponComponent* currentWeapon = FindComponent<WeaponComponent>();
	int projectileCount = 0;
	if (currentWeapon != NULL)
	{
		// Establece el número de proyectiles disparados igual al anterior
		projectileCount = currentWeapon->projectileCount;

		// Hace CleanUp y destruye el arma anterior
		currentWeapon->CleanUp();
		RemoveComponent(currentWeapon);
		RELEASE(currentWeapon);
	}

	// Hace Start y añade el arma nueva
	AddComponent(newWeapon);
	newWeapon->Start();
	newWeapon->projectileCount = projectileCount;
}
