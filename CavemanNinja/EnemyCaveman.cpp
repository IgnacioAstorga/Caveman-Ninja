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
#include "AIComponent.h"
#include "CavemanAIManager.h"
#include "EntityLifetimeComponent.h"
#include "Transform.h"
#include "GameControllerComponent.h"
#include "Player.h"

void EnemyCaveman::OnCreate()
{
	vector<int> collisionsTypes;
	collisionsTypes.push_back(PLAYER);

	// A�ade las componentes de la entidad
	ColliderComponent* colliderComponent;
	CircleColliderComponent* attackComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_caveman_1.png", EnemyCavemanAnimator::Create(), -64, -128));
	AddComponent(colliderComponent = new RectangleColliderComponent(25, 46, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -23, 0, ENEMY, true));
	AddComponent(attackComponent = new CircleColliderComponent(20, collisionsTypes, 0, -23, ENEMY_ATTACK, false, false));
	AddComponent(new AIComponent(CavemanAIManager::Create(attackComponent, colliderComponent)));
	AddComponent(new DieOnPlayerAttackComponent(1.25f, colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new EnemyGravityComponent(500.0f, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false));
	AddComponent(new EnemyAnimatorMappingComponent());

	// A�ade el componente que hace aparecer un pickup de forma aleatoria
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

void EnemyCaveman::Kill()
{
	// Mata al personaje directamente
	FindComponent<DieOnPlayerAttackComponent>()->Die(GameController->player->transform);
}
