#include "Animation.h"

Animation::Animation(bool start_enabled)
	: enabled(start_enabled) {};

Animation::~Animation() {};

bool Animation::IsEnabled() const
{
	return enabled;
}

bool Animation::Enable()
{
	if (enabled == false)
		return enabled = Start();
	return true;
};

bool Animation::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();
	return true;
};