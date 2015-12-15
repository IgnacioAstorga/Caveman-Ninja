#include "BasicAnimation.h"

#include "SDL.h"

BasicAnimation::BasicAnimation(float speed, bool start_enabled) : enabled(start_enabled)
{
	this->speed = speed;
}

bool BasicAnimation::Start()
{
	current_frame = 0.0f;
	return true;
}

SDL_Rect& BasicAnimation::GetCurrentFrame()
{
	return frames[(int)current_frame];
}

void BasicAnimation::Increment(float amount)
{
	current_frame += speed * amount;
	if (speed >= 0 && current_frame >= frames.size())
		current_frame = 0.0f;
	if (speed < 0 && current_frame < 0)
		current_frame = (float) (frames.size() - 1);
}