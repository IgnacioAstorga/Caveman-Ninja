#ifndef __GUITTEXTRENDERERCOMPONENT_H__
#define __GUITTEXTRENDERERCOMPONENT_H__

#include "GUITextureRendererComponent.h"
#include "Color.h"

#include "SDL_ttf.h"

#include <string>

using namespace std;

class GUITextRendererComponent : public GUITextureRendererComponent
{
public:
	GUITextRendererComponent(string text, string fontName, unsigned int size, Color color = WHITE, GUILocation align = TOP_LEFT, float offsetX = 0.0f, float offsetY = 0.0f, GUILocation location = TOP_LEFT, bool shadow = false, fPoint shadowOffset = { 0, 0 }, bool start_enabled = true);
	virtual ~GUITextRendererComponent();

protected:
	SDL_Texture* OnLoadTexture();

public:
	void SetText(string text);
	string GetText();
	void SetFont(string fontName);
	void SetFont(string fontName, unsigned int size);
	string GetFontName();
	void SetSize(unsigned int size);
	unsigned int GetSize();
	void SetColor(Color color);
	Color GetColor();

private:
	SDL_Texture* CreateTexture();

private:
	string text;
	string fontName;
	unsigned int size;
	Color color;
	GUILocation align;
	TTF_Font* font;

	fPoint storedOffset;
};

#endif //  __GUITTEXTRENDERERCOMPONENT_H__
