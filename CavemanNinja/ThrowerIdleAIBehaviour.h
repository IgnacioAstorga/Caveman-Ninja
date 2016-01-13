#ifndef __THROWERIDLEAIBEHAVIOUR_H__
#define __THROWERIDLEAIBEHAVIOUR_H__

#include "AIBehaviour.h"

class ThrowerIdleAIBehaviour : public AIBehaviour
{
public:
	ThrowerIdleAIBehaviour();
	virtual ~ThrowerIdleAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();
};
#endif // __THROWERIDLEAIBEHAVIOUR_H__