#include "FangBigProjectile.h"
#include "SpriteRendererComponent.h"
#include "MovementSimpleComponent.h"
#include "RectangleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "WeaponAnimatorMappingComponent.h"
#include "ColliderTypes.h"
#include "SingleAnimation.h"

#define LIFETIME 0.7f

void FangBigProjectile::OnCreate()
{
	AddComponent(new SpriteRendererComponent("assets/images/weapon_fang_big.png", new SingleAnimation(32, 32), -16, -15));
	AddComponent(new WeaponAnimatorMappingComponent());
	AddComponent(new MovementSimpleComponent());
	AddComponent(new RectangleColliderComponent(32.0f, 12.0f, { FLOOR, ENEMY, EGG }, 0.0f, 0.0f, 0.0f, PLAYER_ATTACK, true));
	AddComponent(new WeaponLifespanComponent(LIFETIME));
}

void FangBigProjectile::OnDestroy()
{
	// En principio no hace nada
}