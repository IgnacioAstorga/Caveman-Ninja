#ifndef __THROWERTHROWDOAIBEHAVIOUR_H__
#define __THROWERTHROWDOAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class ThrowerThrowDoAIBehaviour : public AIBehaviour
{
public:
	ThrowerThrowDoAIBehaviour();
	virtual ~ThrowerThrowDoAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANATTACKAIBEHAVIOUR_H__