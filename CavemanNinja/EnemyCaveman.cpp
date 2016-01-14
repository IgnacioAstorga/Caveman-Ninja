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
#include "FoodPickup.h"
#include "SpawnFoodPickupOnDeathComponent.h"
#include "AIComponent.h"
#include "CavemanAIManager.h"
#include "EntityLifetimeComponent.h"
#include "Random.h"

#define ATTACK_RADIUS 20.0f
#define DECAY_TIME 1.25f
#define FLY_SPEED { 100.0f, -150.0f }
#define GRAVITY 500.0f
#define MEAT_CHANCE 0.1f

void EnemyCaveman::OnCreate()
{
	vector<int> collisionsTypes;
	collisionsTypes.push_back(PLAYER);

	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	CircleColliderComponent* attackComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_caveman.png", EnemyCavemanAnimator::Create(), -64, -128));
	AddComponent(colliderComponent = new RectangleColliderComponent(25, 46, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -23, 0, ENEMY, true));
	AddComponent(attackComponent = new CircleColliderComponent(ATTACK_RADIUS, collisionsTypes, 0, 0, ENEMY_ATTACK, false, false));
	AddComponent(new AIComponent(CavemanAIManager::Create(attackComponent, colliderComponent)));
	AddComponent(new DieOnPlayerAttackComponent(DECAY_TIME, FLY_SPEED, "assets/sounds/enemy_caveman_die.wav", colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new EnemyGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false));
	AddComponent(new EnemyAnimatorMappingComponent());

	// Añade el componente que hace aparecer un pickup de forma aleatoria
	FoodPickupType type;
	if (Random().Value() < MEAT_CHANCE)	// Probabilidad de que sea carne
		type = FOOD_MEAT;
	else
		type = FOOD_SMALL;
	AddComponent(new SpawnFoodPickupOnDeathComponent(type));
}

void EnemyCaveman::OnDestroy()
{
	// No hace nada
}