#ifndef __BASICANIMATION_H__
#define __BASICANIMATION_H__

#include "Animation.h"

#include <vector>

class BasicAnimation : public Animation
{
public:
	BasicAnimation(float speed = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE, bool loop = true, bool start_enabled = true);

	bool Start();

public:
	SDL_Rect& GetCurrentFrame();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);
	void Increment(float amount);
	bool IsFinished();

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