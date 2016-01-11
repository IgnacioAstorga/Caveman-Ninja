#ifndef __CAVEMANATTACKAIBEHAVIOUR_H__
#define __CAVEMANATTACKAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanAttackAIBehaviour : public AIBehaviour
{
public:
	CavemanAttackAIBehaviour();
	virtual ~CavemanAttackAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANATTACKAIBEHAVIOUR_H__