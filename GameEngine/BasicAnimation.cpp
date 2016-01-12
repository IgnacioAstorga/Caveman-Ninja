#include "BasicAnimation.h"

#include "SDL.h"

BasicAnimation::BasicAnimation(int width, int height, int columns, int rows, float speed, bool loop, SDL_RendererFlip flip, bool start_enabled) : enabled(start_enabled)
{
	this->width = width;
	this->height = height;
	this->rows = rows;
	this->columns = columns;
	this->speed = speed;
	this->flip = flip;
	this->loop = loop;
}

bool BasicAnimation::Start()
{
	current_frame = 0.0f;
	finished = false;
	frameWidth = width / columns;
	frameHeight = height / rows;
	return true;
}

SDL_Rect BasicAnimation::GetCurrentFrame() const
{
	iPoint frame = frames[(int)current_frame];
	SDL_Rect rect { frame.x * frameWidth, frame.y * frameHeight, frameWidth, frameHeight };
	return rect;
}

SDL_RendererFlip BasicAnimation::GetFlip() const
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

bool BasicAnimation::IsFinished() const
{
	return finished;
}
