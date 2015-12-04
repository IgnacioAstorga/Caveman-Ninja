#include "Animation.h"

#include "SDL.h"

Animation::Animation()
{
	speed = 1.0f;
	current_frame = 0.0f;
}

SDL_Rect& Animation::GetCurrentFrame()
{
	current_frame += speed;
	if (current_frame >= frames.size())
		current_frame = 0.0f;

	return frames[(int)current_frame];
}