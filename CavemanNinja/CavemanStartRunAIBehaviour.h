#ifndef __CAVEMANSTARTRUNAIBEHAVIOUR_H__
#define __CAVEMANSTARTRUNAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanStartRunAIBehaviour : public AIBehaviour
{
public:
	CavemanStartRunAIBehaviour();
	virtual ~CavemanStartRunAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANSTARTRUNAIBEHAVIOUR_H__