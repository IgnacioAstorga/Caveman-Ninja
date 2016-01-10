#ifndef __AICAVEMANCOMPONENT_H__
#define __AICAVEMANCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

enum IACavemanState
{
	IDLE,
	SEARCH,
	CHARGE,
	ATTACK,
	START_RUN,
	RUN
};

class DieOnPlayerAttackComponent;
class ColliderComponent;
class CircleColliderComponent;
class EntityLifetimeComponent;

class AICavemanComponent : public Component
{
public:
	AICavemanComponent(CircleColliderComponent* attackComponent, ColliderComponent* hitboxComponent, float frecuency);
	virtual ~AICavemanComponent();

protected:
	bool OnStart();
	bool OnCleanUp();
	bool OnUpdate();

public:
	void SetState(IACavemanState state);
	IACavemanState GetState();
	int GetOrientation();
	void SetFrecuency(float frecuency, bool reset = false);

private:
	void TickIA();
	void TickIDLE();
	void TickSEARCH();
	void TickCHARGE();
	void TickATTACK();
	void TickSTART_RUN();
	void TickRUN();

private:
	IACavemanState state;
	int orientation;

	float timeBeetwenTicks;
	float timeSinceLastTick;

	unsigned int runStartSound;
	unsigned int runSound;

public:
	Timer timer;
	CircleColliderComponent* attackComponent;
	ColliderComponent* hitboxComponent;
	EntityLifetimeComponent* lifetimeComponent;
};
#endif //__AICAVEMANCOMPONENT_H__