#ifndef __GUITSPRITERENDERERCOMPONENT_H__
#define __GUITSPRITERENDERERCOMPONENT_H__

#include "GUITextureRendererComponent.h"

#include <string>

using namespace std;

class GUISpriteRendererComponent : public GUITextureRendererComponent
{
public:
	GUISpriteRendererComponent(string fileName, Animation* animation = nullptr, float offsetX = 0.0f, float offsetY = 0.0f, GUILocation location = ABSOLUTE, bool start_enabled = true);
	virtual ~GUISpriteRendererComponent();

protected:
	SDL_Texture* OnLoadTexture();

public:
	Animation* GetAnimation();

private:
	string fileName;
};

#endif //  __GUITSPRITERENDERERCOMPONENT_H__
