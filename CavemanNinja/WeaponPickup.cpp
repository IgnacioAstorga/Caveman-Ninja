#include "WeaponPickup.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "CircleColliderComponent.h"
#include "ColliderTypes.h"
#include "OnWeaponPickUpComponent.h"
#include "EntityLifetimeComponent.h"

#define PICKUP_LIFETIME 20.0f

WeaponPickup::WeaponPickup(WeaponPickupType type, string name, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	this->type = type;
	OnCreate();
}

void WeaponPickup::OnCreate()
{
	// Crea la animación adecuada de la entidad
	BasicAnimation* animation = new BasicAnimation(128, 64, 4, 2, 0.0f, false);
	animation->frames.push_back({ type % 4, type / 2 });

	// Crea el vector con los tipos de colliders ("{}" no soporta un solo elemento)
	vector<int> collisionsTypes;
	collisionsTypes.push_back(PLAYER);

	// Crea los componentes de la entidad
	AddComponent(new SpriteRendererComponent("assets/images/pickups_weapons.png", animation, -16, -32));
	AddComponent(new CircleColliderComponent(16, collisionsTypes, 0, -16, PICKUP));
	AddComponent(new OnWeaponPickUpComponent(type));
	AddComponent(new EntityLifetimeComponent(PICKUP_LIFETIME));
}

void WeaponPickup::OnDestroy()
{
	// En principio no hace nada
}
