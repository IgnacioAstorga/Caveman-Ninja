#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL_render.h"

struct SDL_Rect;

class Animation
{
public:
	Animation(bool start_enabled = true);
	virtual ~Animation();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	virtual SDL_Rect GetCurrentFrame() const = 0;
	virtual SDL_RendererFlip GetFlip() const = 0;
	virtual void SetFlip(SDL_RendererFlip flip) = 0;
	virtual void Increment(float amount) = 0;
	virtual bool IsFinished() const = 0;

protected:
	bool enabled;
};
#endif //__ANIMATION_H__