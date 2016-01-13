#ifndef __CAVEMANRUNAIBEHAVIOUR_H__
#define __CAVEMANRUNAIBEHAVIOUR_H__

#include "AIBehaviour.h"

class CavemanRunAIBehaviour : public AIBehaviour
{
public:
	CavemanRunAIBehaviour();
	virtual ~CavemanRunAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();
};
#endif // __CAVEMANRUNAIBEHAVIOUR_H__