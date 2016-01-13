#ifndef __THROWERTHROWSTARTAIBEHAVIOUR_H__
#define __THROWERTHROWSTARTAIBEHAVIOUR_H__

#include "AIBehaviour.h"

class Animator;

class ThrowerThrowStartAIBehaviour : public AIBehaviour
{
public:
	ThrowerThrowStartAIBehaviour();
	virtual ~ThrowerThrowStartAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Animator* animator;
};
#endif // __THROWERTHROWSTARTAIBEHAVIOUR_H__