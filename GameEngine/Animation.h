#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

struct SDL_Rect;

class Animation
{
public:
	Animation();
	SDL_Rect& GetCurrentFrame();

	float speed;
	std::vector<SDL_Rect> frames;

private:
	float current_frame;
};

#endif //__ANIMATION_H__