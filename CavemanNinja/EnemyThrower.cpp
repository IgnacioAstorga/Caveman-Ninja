#include "EnemyThrower.h"
#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "EnemyThrowerAnimator.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "EnemyGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "DieOnPlayerAttackComponent.h"
#include "EnemyAnimatorMappingComponent.h"
#include "FoodPickup.h"
#include "SpawnFoodPickupOnDeathComponent.h"
#include "AIComponent.h"
#include "ThrowerAIManager.h"
#include "EntityLifetimeComponent.h"
#include "Random.h"

#define DECAY_TIME 1.25f
#define FLY_SPEED { 100.0f, -150.0f }
#define GRAVITY 500.0f
#define MEAT_CHANCE 0.1f

void EnemyThrower::OnCreate()
{
	vector<int> collisionsTypes;
	collisionsTypes.push_back(PLAYER);

	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_caveman.png", EnemyThrowerAnimator::Create(), -64, -128));
	AddComponent(colliderComponent = new RectangleColliderComponent(25, 46, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -23, 0, ENEMY, true));
	AddComponent(new AIComponent(ThrowerAIManager::Create(colliderComponent)));
	AddComponent(new DieOnPlayerAttackComponent(DECAY_TIME, FLY_SPEED, "assets/sounds/enemy_caveman_die.wav", colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new EnemyGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false));
	AddComponent(new EnemyAnimatorMappingComponent());

	// Añade el componente que hace aparecer un pickup de forma aleatoria
	FoodPickupType type;
	if (Random().Value() < MEAT_CHANCE)	// 1 entre 10 de que sea carne
		type = FOOD_MEAT;
	else
		type = FOOD_SMALL;
	AddComponent(new SpawnFoodPickupOnDeathComponent(type));
}

void EnemyThrower::OnDestroy()
{
	// No hace nada
}