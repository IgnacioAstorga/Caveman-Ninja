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
	AddComponent(colliderComponent = new CircleColliderComponent(11.0f, 0.0f, 0.0f, PLAYER_ATTACK, true));
	AddComponent(new WeaponGravityComponent(500.0f, FLOOR, colliderComponent));
	AddComponent(new WeaponLifespanComponent(1.15f, weaponComponent));
	AddComponent(new WeaponDestroyOnCollisionComponent(ENEMY));
}

void TomahawkProjectile::OnDestroy()
{
	// En principio no hace nada
}