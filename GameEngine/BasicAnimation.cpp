#include "BasicAnimation.h"

#include "SDL.h"

BasicAnimation::BasicAnimation(float speed, SDL_RendererFlip flip, bool loop, bool start_enabled) : enabled(start_enabled)
{
	this->speed = speed;
	this->flip = flip;
	this->loop = loop;
}

bool BasicAnimation::Start()
{
	current_frame = 0.0f;
	finished = false;
	return true;
}

SDL_Rect& BasicAnimation::GetCurrentFrame()
{
	return frames[(int)current_frame];
}

SDL_RendererFlip BasicAnimation::GetFlip()
{
	return flip;
}

void BasicAnimation::SetFlip(SDL_RendererFlip flip)
{
	this->flip = flip;
}

void BasicAnimation::Increment(float amount)
{
	current_frame += speed * amount;
	if (speed >= 0 && current_frame >= frames.size())
		if (loop)
			current_frame = 0.0f;	// En loop la animación no termina
		else
		{
			current_frame = (float)(frames.size() - 1);
			finished = true;
		}
	if (speed < 0 && current_frame < 0)
		if (loop)
			current_frame = (float)(frames.size() - 1);	// En loop la animación no termina
		else
		{
			current_frame = 0.0f;
			finished = true;
		}
}

bool BasicAnimation::IsFinished()
{
	return finished;
}
