#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
public:
	Color() : Color(1.0f, 1.0f, 1.0f, 1.0f) {}

	Color(float red, float green, float blue) : Color(red, green, blue, 1.0f) {}

	Color(float red, float green, float blue, float alpha) {
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	float red;
	float green;
	float blue;
	float alpha;
};
#endif // __COLOR_H__