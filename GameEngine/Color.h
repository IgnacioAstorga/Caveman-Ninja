#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
public:
	Color() {
		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
		alpha = 1.0f;
	}

	float red;
	float green;
	float blue;
	float alpha;
};
#endif // __COLOR_H__