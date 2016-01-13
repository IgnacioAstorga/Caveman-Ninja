#ifndef __CAVEMANRUNSTARTAIBEHAVIOUR_H__
#define __CAVEMANRUNSTARTAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanRunStartAIBehaviour : public AIBehaviour
{
public:
	CavemanRunStartAIBehaviour();
	virtual ~CavemanRunStartAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANSTARTRUNAIBEHAVIOUR_H__