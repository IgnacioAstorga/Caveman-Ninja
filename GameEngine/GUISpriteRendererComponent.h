#ifndef __GUITSPRITERENDERERCOMPONENT_H__
#define __GUITSPRITERENDERERCOMPONENT_H__

#include "GUITextureRendererComponent.h"

#include <string>

using namespace std;

class GUISpriteRendererComponent : public GUITextureRendererComponent
{
public:
	GUISpriteRendererComponent(string fileName, Animation* animation = nullptr, float offsetX = 0.0f, float offsetY = 0.0f, GUILocation location = TOP_LEFT, bool shadow = false, fPoint shadowOffset = { 0, 0 }, bool start_enabled = true);
	virtual ~GUISpriteRendererComponent();

protected:
	SDL_Texture* OnLoadTexture();

public:
	Animation* GetAnimation() const;

private:
	string fileName;
};

#endif //  __GUITSPRITERENDERERCOMPONENT_H__
