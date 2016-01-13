#ifndef __THROWERAIMANAGER_H__
#define __THROWERAIMANAGER_H__

#include "EnemyAIManager.h"

enum CavemanAIState
{
	IDLE,
	THROW_START,
	THROW_DO,
	RUN_START,
	RUN
};

class CircleColliderComponent;
class ColliderComponent;
class EntityLifetimeComponent;

class ThrowerAIManager : public EnemyAIManager
{
public:
	ThrowerAIManager(ColliderComponent* hitboxComponent, AIState* initialState, float frecuency);
	virtual ~ThrowerAIManager();

protected:
	bool OnStart();
	bool OnCleanUp();

public:
	static ThrowerAIManager* Create(ColliderComponent* hitboxComponent);

public:
	ColliderComponent* hitboxComponent;
	EntityLifetimeComponent* lifetimeComponent;

	unsigned int throwSound;
	unsigned int runStartSound;
	unsigned int runSound;
};
#endif // __THROWERAIMANAGER_H__