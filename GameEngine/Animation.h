#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

struct SDL_Rect;

class Animation
{
public:
	Animation(float speed = 1.0f, bool start_enabled = true);

	bool IsEnabled();
	bool Enable();
	bool Disable();

	bool Start();
	bool CleanUp();

public:
	SDL_Rect& GetCurrentFrame();
	void Increment(float amount);

	float speed;
	std::vector<SDL_Rect> frames;

private:
	bool enabled;
	float current_frame;
};

#endif //__ANIMATION_H__