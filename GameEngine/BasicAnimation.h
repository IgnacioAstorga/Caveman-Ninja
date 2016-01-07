#ifndef __BASICANIMATION_H__
#define __BASICANIMATION_H__

#include "Animation.h"
#include "Point.h"

#include <vector>

class BasicAnimation : public Animation
{
public:
	BasicAnimation(int width, int height, int columns, int rows, float speed = 1.0f, bool loop = true, SDL_RendererFlip flip = SDL_FLIP_NONE, bool start_enabled = true);

	bool Start();

public:
	SDL_Rect GetCurrentFrame();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);
	void Increment(float amount);
	bool IsFinished();

public:
	int width;
	int height;
	int columns;
	int rows;
	float speed;
	SDL_RendererFlip flip;
	bool loop;
	std::vector<iPoint> frames;

private:
	bool enabled;
	float current_frame;
	bool finished;
	int frameWidth;
	int frameHeight;
};

#endif // __BASICANIMATION_H__