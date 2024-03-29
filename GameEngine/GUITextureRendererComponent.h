#ifndef __GUITEXTURERENDERERCOMPONENT_H__
#define __GUITEXTURERENDERERCOMPONENT_H__

#include "GUIComponent.h"

class Animation;
struct SDL_Texture;

class GUITextureRendererComponent : public GUIComponent
{
public:
	GUITextureRendererComponent(Animation* animation = nullptr, float offsetX = 0.0f, float offsetY = 0.0f, GUILocation location = TOP_LEFT, bool shadow = false, fPoint shadowOffset = { 0, 0 }, bool start_enabled = true);
	virtual ~GUITextureRendererComponent();

	bool GUIStart();
	bool GUICleanUp();

	bool GUIPostUpdate();

protected:
	virtual SDL_Texture* OnLoadTexture() = 0;	// M�todo encargado de cargar la textura adecuada

protected:
	fPoint GetReferencePosition() const;

protected:
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	float offsetX, offsetY;
	bool shadow;
	fPoint shadowOffset;
};

#endif //  __GUISPRITERENDERERCOMPONENT_H__
