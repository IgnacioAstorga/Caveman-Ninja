#ifndef __BASICANIMATION_H__
#define __BASICANIMATION_H__

#include "Animation.h"

#include <vector>

struct SDL_Rect;

class BasicAnimation : public Animation
{
public:
	BasicAnimation(float speed = 1.0f, bool start_enabled = true);

	bool Start();

public:
	SDL_Rect& GetCurrentFrame();
	void Increment(float amount);

	float speed;
	std::vector<SDL_Rect> frames;

private:
	bool enabled;
	float current_frame;
};

#endif // __BASICANIMATION_H__