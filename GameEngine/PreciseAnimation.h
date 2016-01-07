#ifndef __PRECISEANIMATION_H__
#define __PRECISEANIMATION_H__

#include "Animation.h"

#include <vector>

class PreciseAnimation : public Animation
{
public:
	PreciseAnimation(float speed = 1.0f, bool loop = true, SDL_RendererFlip flip = SDL_FLIP_NONE, bool start_enabled = true);

	bool Start();

public:
	SDL_Rect GetCurrentFrame();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);
	void Increment(float amount);
	bool IsFinished();

public:
	float speed;
	SDL_RendererFlip flip;
	bool loop;
	std::vector<SDL_Rect> frames;

private:
	bool enabled;
	float current_frame;
	bool finished;
};

#endif // __BASICANIMATION_H__