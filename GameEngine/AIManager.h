#ifndef __AIMANAGER_H__
#define __AIMANAGER_H__

#include "StateMachine.h"
#include "AIBehaviour.h"
#include "Timer.h"

typedef StateSwitcher<AIBehaviour> AIState;
typedef StateTransition<AIBehaviour> AITransition;

class Entity;

class AIManager : public StateMachine<AIBehaviour>
{
public:
	AIManager(AIState* initialState, float frecuency);
	virtual ~AIManager();

public:
	bool Start();
	bool CleanUp();

	bool Update();

public:
	void SetFrecuency(float frecuency);
	void SetDelay(float delay);
	void Configure(Entity* entity);

protected:
	void OnStateTransition(AIBehaviour* lastState, AIBehaviour* newState);

	virtual bool OnStart() { return true; }
	virtual bool OnCleanUp() { return true; }

protected:
	float delay;
	Timer delayTimer;

	Entity* entity;
};

#endif // __AIMANAGER_H__