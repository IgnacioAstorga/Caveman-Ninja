#ifndef __ENEMYSPAWNER_H__
#define __ENEMYSPAWNER_H__

#include "Entity.h"

class Enemy;

class EnemySpawner : public Entity
{
public:
	EnemySpawner(Enemy* enemy, float positionX = 0.0f, float positionY = 0.0f);
	virtual ~EnemySpawner() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	Enemy* enemy;
};
#endif	// __ENEMYSPAWNER_H__