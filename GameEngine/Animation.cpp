#include "Animation.h"

#include "SDL.h"

Animation::Animation(float speed, bool start_enabled) : enabled(start_enabled)
{
	this->speed = speed;
}

bool Animation::IsEnabled()
{
	return enabled;
}

bool Animation::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
}

bool Animation::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
}

bool Animation::Start()
{
	current_frame = 0.0f;
	return true;
}

bool Animation::CleanUp()
{
	// No hace nada en concreto
	return true;
}

SDL_Rect& Animation::GetCurrentFrame()
{
	return frames[(int)current_frame];
}

void Animation::Increment(float amount)
{
	current_frame += speed * amount;
	if (current_frame >= frames.size())
		current_frame = 0.0f;
}