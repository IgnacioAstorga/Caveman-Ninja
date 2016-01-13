#include "TomahawkProjectile.h"
#include "TomahawkAnimator.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "MovementSimpleComponent.h"
#include "WeaponGravityComponent.h"
#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "WeaponAnimatorMappingComponent.h"
#include "WeaponDestroyOnCollisionComponent.h"

#define GRAVITY 500.0f
#define LIFETIME 1.15f

TomahawkProjectile::TomahawkProjectile(WeaponComponent * weaponComponent, std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	this->weaponComponent = weaponComponent;
	OnCreate();
}

void TomahawkProjectile::OnCreate()
{
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/weapon_tomahawk.png", TomahawkAnimator::Create(), -16, -16));
	AddComponent(new WeaponAnimatorMappingComponent());
	AddComponent(new MovementSimpleComponent());
	AddComponent(colliderComponent = new CircleColliderComponent(11.0f, { FLOOR, ENEMY }, 0.0f, 0.0f, PLAYER_ATTACK, false));
	AddComponent(new WeaponGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new WeaponLifespanComponent(LIFETIME, weaponComponent));
	AddComponent(new WeaponDestroyOnCollisionComponent(ENEMY, weaponComponent));
}

void TomahawkProjectile::OnDestroy()
{
	// En principio no hace nada
}