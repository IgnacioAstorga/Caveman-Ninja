#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include "Animation.h"
#include "StateMachine.h"

class Animator : public Animation, public StateMachine<Animation>
{
public:
	Animator(StateSwitcher<Animation>* initialStateSwitcher);

	bool Start();
	bool CleanUp();

public:
	SDL_Rect& GetCurrentFrame();
	void Increment(float amount);

protected:
	void OnStateTransition(Animation* lastState, Animation* newState);

	virtual bool OnStart() { return true; }
	virtual bool OnCleanUp() { return true; }
};

#endif // __ANIMATOR_H__