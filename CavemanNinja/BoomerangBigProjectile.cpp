#include "BoomerangBigProjectile.h"
#include "SpriteRendererComponent.h"
#include "MovementSimpleComponent.h"
#include "CircleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "Transform.h"
#include "BasicAnimation.h"
#include "BoomerangAIComponent.h"
#include "ColliderTypes.h"

#define LIFETIME 3.0f
#define RETURN_TIME 0.4f

BoomerangBigProjectile::BoomerangBigProjectile(std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	OnCreate();
}

void BoomerangBigProjectile::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(128, 128, 2, 2, 8.0f);
	animation->frames.push_back({ 0, 0 });
	animation->frames.push_back({ 1, 0 });
	animation->frames.push_back({ 0, 1 });
	animation->frames.push_back({ 1, 1 });

	AddComponent(new SpriteRendererComponent("assets/images/weapon_boomerang_big.png", animation, -32, -32));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new CircleColliderComponent(32.0f, { FLOOR, ENEMY, EGG }, 0.0f, 0.0f, PLAYER_ATTACK_BIG, false));
	AddComponent(new WeaponLifespanComponent(LIFETIME));
	AddComponent(new BoomerangAIComponent(RETURN_TIME));
}

void BoomerangBigProjectile::OnDestroy()
{
	// En principio no hace nada
}