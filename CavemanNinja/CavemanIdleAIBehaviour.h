#ifndef __CAVEMANIDLEAIBEHAVIOUR_H__
#define __CAVEMANIDLEAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanIdleAIBehaviour : public AIBehaviour
{
public:
	CavemanIdleAIBehaviour();
	virtual ~CavemanIdleAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANIDLEAIBEHAVIOUR_H__