#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include "Animation.h"
#include "StateMachine.h"

#define ANIMATION_END "_animation_finished"

typedef StateSwitcher<Animation> AnimationState;
typedef StateTransition<Animation> AnimationTransition;

class Animator : public Animation, public StateMachine<Animation>
{
public:
	Animator(AnimationState* initialStateSwitcher);
	virtual ~Animator();

	bool Start();
	bool CleanUp();

public:
	SDL_Rect GetCurrentFrame();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);
	void Increment(float amount);
	bool IsFinished();

protected:
	void OnStateTransition(Animation* lastState, Animation* newState);

	virtual bool OnStart() { return true; }
	virtual bool OnCleanUp() { return true; }

private:
	SDL_RendererFlip storedFlip;
};

#endif // __ANIMATOR_H__