#include "Egg.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "EnemyGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "Transform.h"
#include "DieOnPlayerAttackComponent.h"
#include "SpriteRendererComponent.h"
#include "EggAnimator.h"
#include "EnemyBasicAnimatorMappingComponent.h"
#include "EntityLifetimeComponent.h"
#include "SpawnWeaponPickupOnDeathComponent.h"
#include "ActivateComponentAfterTimeComponent.h"

#define DECAY_TIME 1.25f
#define FLY_SPEED { 0.0f, 0.0f }
#define GRAVITY 0.0f
#define FRICTION 0.5f
#define SPEED_DOWN 25.0f
#define NUMBER_OF_WEAPONS 2
#define ACTIVATION_DELAY 0.1f

void Egg::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	DieOnPlayerAttackComponent* lifeComponent;
	AddComponent(new SpriteRendererComponent("assets/images/egg.png", EggAnimator::Create(), -16, -32));
	AddComponent(colliderComponent = new CircleColliderComponent(16, { FLOOR, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -16, EGG));
	AddComponent(lifeComponent = new DieOnPlayerAttackComponent(DECAY_TIME, FLY_SPEED, "assets/sounds/egg_die.wav", colliderComponent, false));
	AddComponent(new EnemyGravityComponent(GRAVITY, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false));
	AddComponent(new EnemyBasicAnimatorMappingComponent());
	AddComponent(new SpawnWeaponPickupOnDeathComponent((WeaponPickupType) (rand() % NUMBER_OF_WEAPONS)));
	AddComponent(new ActivateComponentAfterTimeComponent(ACTIVATION_DELAY, lifeComponent));

	// Lo hace bajar
	transform->speed.y = SPEED_DOWN;
}

void Egg::OnDestroy()
{
	// No hace nada
}