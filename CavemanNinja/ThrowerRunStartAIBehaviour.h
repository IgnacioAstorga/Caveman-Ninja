#ifndef __THROWERRUNSTARTAIBEHAVIOUR_H__
#define __THROWERRUNSTARTAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class ThrowerRunStartAIBehaviour : public AIBehaviour
{
public:
	ThrowerRunStartAIBehaviour();
	virtual ~ThrowerRunStartAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __THROWERRUNSTARTAIBEHAVIOUR_H__