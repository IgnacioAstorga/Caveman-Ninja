#ifndef __CAVEMANCHARGEAIBEHAVIOUR_H__
#define __CAVEMANCHARGEAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanChargeAIBehaviour : public AIBehaviour
{
public:
	CavemanChargeAIBehaviour();
	virtual ~CavemanChargeAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();
};
#endif // __CAVEMANCHARGEAIBEHAVIOUR_H__