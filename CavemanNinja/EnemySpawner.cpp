#include "EnemySpawner.h"
#include "SpawnEntityOnEnterCameraComponent.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(Enemy * enemy, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	this->enemy = enemy;
	OnCreate();
}

void EnemySpawner::OnCreate()
{
	AddComponent(new SpawnEntityOnEnterCameraComponent(enemy));
}

void EnemySpawner::OnDestroy()
{
	// No hace nada
}
