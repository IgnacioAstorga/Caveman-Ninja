#include "TomahawkBigProjectile.h"
#include "TomahawkAnimator.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "MovementSimpleComponent.h"
#include "WeaponGravityComponent.h"
#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "WeaponAnimatorMappingComponent.h"
#include "ColliderTypes.h"

TomahawkBigProjectile::TomahawkBigProjectile(WeaponComponent * weaponComponent, std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	this->weaponComponent = weaponComponent;
	OnCreate();
}

void TomahawkBigProjectile::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(128, 128, 2, 2, 4.0f);
	animation->frames.push_back({ 0, 0 });
	animation->frames.push_back({ 1, 0 });
	animation->frames.push_back({ 0, 1 });
	animation->frames.push_back({ 1, 1 });

	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/weapon_tomahawk_big.png", animation, -32, -32));
	AddComponent(new WeaponAnimatorMappingComponent());
	AddComponent(new MovementSimpleComponent());
	AddComponent(colliderComponent = new CircleColliderComponent(22.0f, { FLOOR, ENEMY }, 0.0f, 0.0f, PLAYER_ATTACK_BIG, false));
	AddComponent(new WeaponGravityComponent(500.0f, colliderComponent));
	AddComponent(new WeaponLifespanComponent(2.0f, weaponComponent));
}

void TomahawkBigProjectile::OnDestroy()
{
	// En principio no hace nada
}