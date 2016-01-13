#ifndef __CAVEMANAIMANAGER_H__
#define __CAVEMANAIMANAGER_H__

#include "AIManager.h"

#define STATE "_state"

#define LEFT -1
#define RIGHT 1

enum CavemanAIState
{
	IDLE,
	SEARCH,
	CHARGE,
	ATTACK,
	START_RUN,
	RUN
};

class CircleColliderComponent;
class ColliderComponent;
class EntityLifetimeComponent;

class CavemanAIManager : public AIManager
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
	int orientation;

	CircleColliderComponent* attackComponent;
	ColliderComponent* hitboxComponent;
	EntityLifetimeComponent* lifetimeComponent;

	unsigned int runStartSound;
	unsigned int runSound;
};
#endif // __CAVEMANAIMANAGER_H__