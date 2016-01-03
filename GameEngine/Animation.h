#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL_render.h"

struct SDL_Rect;

class Animation
{
public:
	Animation(bool start_enabled = true) : enabled(start_enabled) {};
	virtual ~Animation() {};

	bool Animation::IsEnabled()
	{
		return enabled;
	}

	bool Enable()
	{
		if (enabled == false)
			return enabled = Start();
		return true;
	};

	bool Disable()
	{
		if (enabled == true)
			return enabled = !CleanUp();
		return true;
	};

	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:
	virtual SDL_Rect& GetCurrentFrame() = 0;
	virtual SDL_RendererFlip GetFlip() = 0;
	virtual void SetFlip(SDL_RendererFlip flip) = 0;
	virtual void Increment(float amount) = 0;
	virtual bool IsFinished() = 0;

protected:
	bool enabled;
};
#endif //__ANIMATION_H__