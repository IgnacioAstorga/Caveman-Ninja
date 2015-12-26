#ifndef __GUISPRITERENDERERCOMPONENT_H__
#define __GUISPRITERENDERERCOMPONENT_H__

#include "GUIComponent.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Animation.h"
#include "ModuleAnimation.h"

#include "SDL.h"

using namespace std;

class GUISpriteRendererComponent : public GUIComponent
{
public:
	GUISpriteRendererComponent(string textureName, Animation* animation = nullptr, float offsetX = 0.0f, float offsetY = 0.0f, GUILocation location = ABSOLUTE, bool start_enabled = true) : GUIComponent(location, start_enabled)
	{
		this->textureName = textureName;
		this->animation = animation;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	}

	~GUISpriteRendererComponent()
	{
		RELEASE(animation);
	}

	bool GUIStart()
	{
		texture = App->textures->Load(textureName.c_str());
		if (texture == nullptr)
			return false;

		if (animation != nullptr)
			App->animation->RegisterAnimation(animation);

		return true;
	}

	bool GUICleanUp()
	{
		if (texture == nullptr)
			return false;
		App->textures->Unload(texture);

		if (animation != nullptr)
			App->animation->UnregisterAnimation(animation);

		return true;
	}

	bool GUIPostUpdate()
	{
		if (texture == nullptr || entity == nullptr)
			return false;

		// Determina la posici�n de la imagen en pantalla
		fPoint temp = fPoint(offsetX, offsetY);
		temp.x *= entity->transform->GetGlobalScale().x;
		temp.y *= entity->transform->GetGlobalScale().y;
		fPoint renderPosition = GetReferencePosition();
		renderPosition += temp.Rotate(entity->transform->GetGlobalRotation());

		// Determina la rotaci�n de la imagen en pantalla
		float renderRotation = entity->transform->GetGlobalRotation();
		SDL_Point pivot;
		pivot.x = 0;
		pivot.y = 0;

		// Determina la escala de la imagen en pantalla
		fPoint renderScale = entity->transform->GetGlobalScale();

		// Determina el frame que pintar
		SDL_Rect* renderArea = NULL;
		if (animation != nullptr)
			renderArea = &(animation->GetCurrentFrame());

		App->renderer->Blit(texture, (int)renderPosition.x, (int)renderPosition.y, renderRotation, &pivot, renderArea, renderScale);

		return true;
	}

private:
	fPoint GetReferencePosition()
	{
		SDL_Rect viewArea = App->renderer->activeCamera->GetViewArea();
		fPoint origin = fPoint((float)viewArea.x, (float)viewArea.y);
		fPoint position = entity->transform->GetGlobalPosition();

		// Determina la posici�n adecuada del elemento
		switch (location)
		{
		case ABSOLUTE:
			return position;
		case CENTER:
			return origin + position + fPoint((float)viewArea.w / (2 * SCREEN_SIZE), (float)viewArea.h / (2 * SCREEN_SIZE));
		case TOP:
			return origin + position + fPoint((float)viewArea.w / (2 * SCREEN_SIZE), 0.0f);
		case BOTTOM:
			return origin + position + fPoint((float)viewArea.w / (2 * SCREEN_SIZE), (float)viewArea.h / SCREEN_SIZE);
		case LEFT:
			return origin + position + fPoint(0.0f, (float)viewArea.h / (2 * SCREEN_SIZE));
		case RIGHT:
			return origin + position + fPoint((float)viewArea.w / SCREEN_SIZE, (float)viewArea.h / (2 * SCREEN_SIZE));
		case TOP_LEFT:
			return origin + position + fPoint(0.0f, 0.0f);
		case TOP_RIGHT:
			return origin + position + fPoint((float)viewArea.w / SCREEN_SIZE, 0.0f);
		case BOTTOM_LEFT:
			return origin + position + fPoint(0.0f, (float)viewArea.h / SCREEN_SIZE);
		case BOTTOM_RIGHT:
			return origin + position + fPoint((float)viewArea.w / SCREEN_SIZE, (float)viewArea.h / SCREEN_SIZE);
		default:
			return position;
		}
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	float offsetX, offsetY;
};

#endif //  __GUISPRITERENDERERCOMPONENT_H__