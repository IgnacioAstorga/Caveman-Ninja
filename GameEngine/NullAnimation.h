#ifndef __NULLANIMATION_H__
#define __NULLANIMATION_H__

#include "Animation.h"

class NullAnimation : public Animation
{
public:
	NullAnimation() {};
	virtual ~NullAnimation() {};

public:
	virtual SDL_Rect GetCurrentFrame() const { return SDL_Rect(); };
	virtual SDL_RendererFlip GetFlip() const { return SDL_FLIP_NONE; };
	virtual void SetFlip(SDL_RendererFlip flip) {};
	virtual void Increment(float amount) {};
	virtual bool IsFinished() const { return true; };
};
#endif //__NULLANIMATION_H__