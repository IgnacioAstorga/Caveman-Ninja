#ifndef __THROWERRUNAIBEHAVIOUR_H__
#define __THROWERRUNAIBEHAVIOUR_H__

#include "AIBehaviour.h"

class ThrowerRunAIBehaviour : public AIBehaviour
{
public:
	ThrowerRunAIBehaviour();
	virtual ~ThrowerRunAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();
};
#endif // __THROWERRUNAIBEHAVIOUR_H__