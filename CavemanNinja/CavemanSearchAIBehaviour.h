#ifndef __CAVEMANSEARCHAIBEHAVIOUR_H__
#define __CAVEMANSEARCHAIBEHAVIOUR_H__

#include "AIBehaviour.h"
#include "Timer.h"

class CavemanSearchAIBehaviour : public AIBehaviour
{
public:
	CavemanSearchAIBehaviour();
	virtual ~CavemanSearchAIBehaviour();

public:
	void OnEnter();
	void OnTick();
	void OnExit();

private:
	Timer timer;
};
#endif // __CAVEMANSEARCHAIBEHAVIOUR_H__