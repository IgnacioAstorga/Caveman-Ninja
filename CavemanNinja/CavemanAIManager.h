#ifndef __CAVEMANAIMANAGER_H__
#define __CAVEMANAIMANAGER_H__

#include "EnemyAIManager.h"

enum CavemanAIState
{
	IDLE,
	SEARCH,
	CHARGE,
	ATTACK,
	RUN_START,
	RUN
};

class CircleColliderComponent;
class ColliderComponent;
class EntityLifetimeComponent;

class CavemanAIManager : public EnemyAIManager
{
public:
	CavemanAIManager(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent, AIState* initialState, float frecuency);
	virtual ~CavemanAIManager();

protected:
	bool OnStart();
	bool OnCleanUp();

public:
	static CavemanAIManager* Create(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent);

public:
	CircleColliderComponent* attackComponent;
	ColliderComponent* hitboxComponent;
	EntityLifetimeComponent* lifetimeComponent;

	unsigned int runStartSound;
	unsigned int runSound;
};
#endif // __CAVEMANAIMANAGER_H__