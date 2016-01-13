#ifndef __ENEMYAIMANAGER_H__
#define __ENEMYAIMANAGER_H__

#include "AIManager.h"

#define STATE "_state"

#define LEFT -1
#define RIGHT 1

class EnemyAIManager : public AIManager
{
public:
	EnemyAIManager(AIState* initialState, float frecuency) : AIManager(initialState, frecuency) {};
	virtual ~EnemyAIManager() {};

public:
	int orientation;
};
#endif // __ENEMYAIMANAGER_H__