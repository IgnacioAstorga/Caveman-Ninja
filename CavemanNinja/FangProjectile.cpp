#include "FangProjectile.h"
#include "SpriteRendererComponent.h"
#include "MovementSimpleComponent.h"
#include "RectangleColliderComponent.h"
#include "WeaponLifespanComponent.h"
#include "WeaponAnimatorMappingComponent.h"
#include "WeaponDestroyOnCollisionComponent.h"
#include "Transform.h"
#include "SingleAnimation.h"

#define LIFETIME 0.35f

FangProjectile::FangProjectile(bool up, std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{ 
	this->up = up;
	OnCreate();
}

void FangProjectile::OnCreate()
{
	AddComponent(new SpriteRendererComponent("assets/images/weapon_fang.png", new SingleAnimation(16, 16), -8, -7));
	AddComponent(new WeaponAnimatorMappingComponent());
	AddComponent(new MovementSimpleComponent());
	AddComponent(new RectangleColliderComponent(16.0f, 7.0f, { FLOOR, ENEMY, EGG }, 0.0f, 0.0f, 0.0f, PLAYER_ATTACK, false));
	AddComponent(new WeaponLifespanComponent(LIFETIME));
	AddComponent(new WeaponDestroyOnCollisionComponent(ENEMY));
	AddComponent(new WeaponDestroyOnCollisionComponent(EGG));

	// Lo hace mirar hacia arriba si su velocidad horizontal es 0
	if (up)
		transform->rotation = -90.0f;
	else
		transform->rotation = 0.0f;
}

void FangProjectile::OnDestroy()
{
	// En principio no hace nada
}