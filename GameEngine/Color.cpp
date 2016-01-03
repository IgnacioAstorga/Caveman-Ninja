#include "Color.h"
#include "SDL.h"

Color::Color() : Color(1.0f, 1.0f, 1.0f, 1.0f) {}

Color::Color(float red, float green, float blue, float alpha) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

SDL_Color Color::ToSDLColor() const
{
	SDL_Color sdlColor;
	sdlColor.r = (unsigned int)(red * 255);
	sdlColor.g = (unsigned int)(green * 255);
	sdlColor.b = (unsigned int)(blue * 255);
	sdlColor.a = (unsigned int)(alpha * 255);
	return sdlColor;
}