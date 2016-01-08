#include "EnemyCaveman.h"
#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "EnemyCavemanAnimator.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "EnemyGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "DieOnPlayerAttackComponent.h"
#include "EnemyAnimatorMappingComponent.h"
#include "Pickup.h"
#include "SpawnPickupOnDeathComponent.h"

void EnemyCaveman::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_caveman_1.png", EnemyCavemanAnimator::Create(), -64, -128));
	AddComponent(new EnemyAnimatorMappingComponent());
	AddComponent(colliderComponent = new RectangleColliderComponent(25, 46, 0, -23, 0, ENEMY));
	AddComponent(new DieOnPlayerAttackComponent(1.25f, colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, 0.0f, 0.0f, NONE, true));
	AddComponent(new EnemyGravityComponent(500.0f, GROUND, colliderComponent, 5.0f, 0.1f));
	AddComponent(new MovementSimpleComponent());

	// Añade el componente que hace aparecer un pickup de forma aleatoria
	PickupType type;
	if (rand() % 10 == 0)	// 1 entre 10 de que sea carne
		type = FOOD_MEAT;
	else
		type = FOOD_SMALL;
	AddComponent(new SpawnPickupOnDeathComponent(type));

	// Empieza a moverlo
	transform->SetSpeed(-25.0f, 0.0f);
}

void EnemyCaveman::OnDestroy()
{
	// No hace nada
}