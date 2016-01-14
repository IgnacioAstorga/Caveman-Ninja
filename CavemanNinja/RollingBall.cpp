#include "RollingBall.h"
#include "ColliderComponent.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "RollingBallGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "Transform.h"
#include "DieOnPlayerAttackComponent.h"
#include "SpriteRendererComponent.h"
#include "RollingBallAnimator.h"
#include "EnemyBasicAnimatorMappingComponent.h"
#include "EntityLifetimeComponent.h"

#define DECAY_TIME 1.25f
#define FLY_SPEED { 0.0f, 0.0f }
#define GRAVITY 500.0f
#define FRICTION 0.5f

void RollingBall::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_rock.png", RollingBallAnimator::Create(), -24, -38));
	AddComponent(colliderComponent = new CircleColliderComponent(15, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -15, ENEMY));
	AddComponent(new DieOnPlayerAttackComponent(DECAY_TIME, FLY_SPEED, "assets/sounds/enemy_rock_die.wav", colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new RollingBallGravityComponent(GRAVITY, FRICTION, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EntityLifetimeComponent(5.0f, false));
	AddComponent(new EnemyBasicAnimatorMappingComponent());
}

void RollingBall::OnDestroy()
{
	// No hace nada
}