#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include "Animation.h"
#include "StateMachine.h"

class Animator : public Animation, public StateMachine<Animation>
{
public:
	Animator(StateSwitcher<Animation>* initialStateSwitcher);
	virtual ~Animator();

	bool Start();
	bool CleanUp();

public:
	SDL_Rect& GetCurrentFrame();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);
	void Increment(float amount);

protected:
	void OnStateTransition(Animation* lastState, Animation* newState);

	virtual bool OnStart() { return true; }
	virtual bool OnCleanUp() { return true; }

private:
	SDL_RendererFlip storedFlip;
};

#endif // __ANIMATOR_H__