#ifndef __SPRITERENDERERCOMPONENT_H__
#define __SPRITERENDERERCOMPONENT_H__

#include "Component.h"
#include "SDL.h"

#include <string>

class Animation;

using namespace std;

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(string textureName, float rotation = 0.0f);
	SpriteRendererComponent(string textureName, Animation* animation, float rotation = 0.0f);
	SpriteRendererComponent(string textureName, Animation* animation, float offsetX, float offsetY, float rotation = 0.0f, float speed = 1.0f, bool tiledHorizontal = false, bool tiledVertical = false, bool start_enabled = true);
	virtual~SpriteRendererComponent();

	bool OnStart();
	bool OnCleanUp();
	bool OnPostUpdate();

protected:
	virtual void Render(fPoint renderPosition, float renderRotation, SDL_Point* pivot, SDL_Rect* renderArea, fPoint renderScale, SDL_RendererFlip flip, float speed);

public:
	Animation* GetAnimation() const;
	void SetOffset(float x, float y);
	void SetOffset(fPoint offset);

	bool IsVisible();
	void SetVisible(bool visible);

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	fPoint offset;
	float rotation;
	float speed;
	bool tiledHorizontal;
	bool tiledVertical;

	bool visible;

	SDL_Rect renderArea;
};

#endif //  __SPRITERENDERERCOMPONENT_H__