#include "RollingBall.h"
#include "ColliderComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "CircleColliderComponent.h"
#include "RollingBallGravityComponent.h"
#include "MovementSimpleComponent.h"
#include "Transform.h"

void RollingBall::OnCreate()
{
	// Añade las componentes de la entidad
	ColliderComponent* colliderComponent;
	AddComponent(new RectangleColliderComponent(25, 46, { PLAYER, PLAYER_ATTACK }, 0, -23, 0, ENEMY, true));
	AddComponent(colliderComponent = new CircleColliderComponent(1.0f, { FLOOR, GROUND }, 0.0f, 0.0f, ENEMY, true));
	AddComponent(new RollingBallGravityComponent(500.0f, 0.5, colliderComponent));
	AddComponent(new MovementSimpleComponent());
}

void RollingBall::OnDestroy()
{
	// No hace nada
}