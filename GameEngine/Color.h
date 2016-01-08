#ifndef __COLOR_H__
#define __COLOR_H__

#define WHITE Color()
#define RED Color(1.0f, 0.0f, 0.0f)
#define GREEN Color(0.0f, 1.0f, 0.0f)
#define BLUE Color(0.0f, 0.0f, 1.0f)
#define BLACK Color(0.0f, 0.0f, 0.0f)

struct SDL_Color;

class Color
{
public:
	Color();
	Color(float red, float green, float blue, float alpha = 1.0f);

public:
	SDL_Color ToSDLColor() const;

public:
	float red;
	float green;
	float blue;
	float alpha;
};
#endif // __COLOR_H__