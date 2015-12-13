#ifndef __SPRITERENDERERCOMPONENT_H__
#define __SPRITERENDERERCOMPONENT_H__

#include "Component.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Entity.h"
#include "Transform.h"
#include "Animation.h"
#include "ModuleAnimation.h"

#include "SDL.h"

using namespace std;

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(string textureName, float rotation = 0.0f)
		: SpriteRendererComponent(textureName, nullptr, 0.0f, 0.0f, rotation) {}

	SpriteRendererComponent(string textureName, Animation* animation, float rotation = 0.0f)
		: SpriteRendererComponent(textureName, animation, 0.0f, 0.0f, rotation) {}

	SpriteRendererComponent(string textureName, Animation* animation, float offsetX, float offsetY, float rotation = 0.0f, bool start_enabled = true) : Component(start_enabled)
	{
		this->textureName = textureName;
		this->animation = animation;
		offset.x = offsetX;
		offset.y = offsetY;
		this->rotation = rotation;
	}

	bool OnStart()
	{
		texture = App->textures->Load(textureName.c_str());
		if (texture == nullptr)
			return false;

		if (animation != nullptr)
			App->animation->RegisterAnimation(animation);

		return true;
	}

	bool OnleanUp()
	{
		if (texture == nullptr)
			return false;
		App->textures->Unload(texture);

		if (animation != nullptr)
			App->animation->UnregisterAnimation(animation);

		return true;
	}

	bool OnPostUpdate()
	{
		if (texture == nullptr || entity == nullptr)
			return false;

		// Determina la posición de la imagen en pantalla
		fPoint temp = offset;
		temp.x *= entity->transform->GetGlobalScale().x;
		temp.y *= entity->transform->GetGlobalScale().y;
		fPoint renderPosition = entity->transform->GetGlobalPosition();
		renderPosition += temp.Rotate(entity->transform->GetGlobalRotation());

		// Determina la rotación de la imagen en pantalla
		float renderRotation = entity->transform->GetGlobalRotation() + rotation;
		SDL_Point* pivot = new SDL_Point();
		pivot->x = 0;
		pivot->y = 0;

		// Determina la escala de la imagen en pantalla
		fPoint renderScale = entity->transform->GetGlobalScale();

		
		// Determina el frame que pintar
		SDL_Rect* renderArea = NULL;
		if (animation != nullptr)
			renderArea = &(animation->GetCurrentFrame());

		App->renderer->Blit(texture, (int)renderPosition.x, (int)renderPosition.y, renderRotation, pivot, renderArea, renderScale);

		return true;
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	fPoint offset;
	float rotation;
};

#endif //  __SPRITERENDERERCOMPONENT_H__
