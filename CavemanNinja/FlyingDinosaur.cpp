#include "FlyingDinosaur.h"
#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "FlyingDinosaurAnimator.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "EnemyGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "DieOnPlayerAttackComponent.h"
#include "EnemyBasicAnimatorMappingComponent.h"
#include "AIComponent.h"
#include "EntityLifetimeComponent.h"
#include "FlyingDinosaurAIComponent.h"
#include "SpawnEggOnDeathComponent.h"

#define DECAY_TIME 1.25f
#define FLY_SPEED { 0.0f, 0.0f }
#define GRAVITY 500.0f
#define MOVEMENT_SPEED 100.0f
#define MOVEMENT_ACCELERATION 75.0f
#define NUMBER_OF_PASSES 3

void FlyingDinosaur::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/flying_dinosaur.png", FlyingDinosaurAnimator::Create(), -64, -96));
	AddComponent(colliderComponent = new CircleColliderComponent(16, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -16, ENEMY));
	AddComponent(new DieOnPlayerAttackComponent(DECAY_TIME, FLY_SPEED, "assets/sounds/flying_dinosaur_die.wav", colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1, { FLOOR, GROUND }, 0, 0, ENEMY));
	AddComponent(new EnemyGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new FlyingDinosaurAIComponent(MOVEMENT_SPEED, MOVEMENT_ACCELERATION, NUMBER_OF_PASSES));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false)); 
	AddComponent(new EnemyBasicAnimatorMappingComponent());
	AddComponent(new SpawnEggOnDeathComponent());
}

void FlyingDinosaur::OnDestroy()
{
	// No hace nada
}