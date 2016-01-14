#include "BoomerangProjectile.h"
#include "SpriteRendererComponent.h"
#include "MovementSimpleComponent.h"
#include "CircleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "WeaponDestroyOnCollisionComponent.h"
#include "Transform.h"
#include "BasicAnimation.h"
#include "BoomerangAIComponent.h"

#define LIFETIME 3.0f
#define RETURN_TIME 0.4f

BoomerangProjectile::BoomerangProjectile(std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	OnCreate();
}

void BoomerangProjectile::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(64, 64, 2, 2, 8.0f);
	animation->frames.push_back({ 0, 0 });
	animation->frames.push_back({ 1, 0 });
	animation->frames.push_back({ 0, 1 });
	animation->frames.push_back({ 1, 1 });

	AddComponent(new SpriteRendererComponent("assets/images/weapon_boomerang.png", animation, -16, -16));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new CircleColliderComponent(16.0f, { FLOOR, ENEMY, EGG }, 0.0f, 0.0f, PLAYER_ATTACK, false));
	AddComponent(new WeaponLifespanComponent(LIFETIME));
	AddComponent(new BoomerangAIComponent(RETURN_TIME));
	AddComponent(new WeaponDestroyOnCollisionComponent(ENEMY));
	AddComponent(new WeaponDestroyOnCollisionComponent(EGG));
}

void BoomerangProjectile::OnDestroy()
{
	// En principio no hace nada
}