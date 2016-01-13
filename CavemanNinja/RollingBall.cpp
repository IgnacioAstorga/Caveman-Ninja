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

void RollingBall::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new SpriteRendererComponent("assets/images/enemy_rock.png", RollingBallAnimator::Create(), -24, -38));
	AddComponent(colliderComponent = new CircleColliderComponent(15, { PLAYER, PLAYER_ATTACK, PLAYER_ATTACK_BIG }, 0, -15, ENEMY));
	AddComponent(new DieOnPlayerAttackComponent(1.25f, { 0, 0 }, "assets/sounds/enemy_rock_die.wav", colliderComponent));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new RollingBallGravityComponent(500.0f, 0.5, colliderComponent));
	AddComponent(new MovementSimpleComponent());
	AddComponent(new EnemyBasicAnimatorMappingComponent());
}

void RollingBall::OnDestroy()
{
	// No hace nada
}