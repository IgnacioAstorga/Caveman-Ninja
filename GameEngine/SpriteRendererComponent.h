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

	SpriteRendererComponent(string textureName, Animation* animation, float offsetX, float offsetY, float rotation = 0.0f)
	{
		this->textureName = textureName;
		this->animation = animation;
		offset.x = offsetX;
		offset.y = offsetY;
		this->rotation = rotation;
	}

	bool Start()
	{
		texture = App->textures->Load(textureName.c_str());
		if (texture == nullptr)
			return false;

		if (animation != nullptr)
			App->animation->RegisterAnimation(animation);

		return true;
	}

	bool CleanUp()
	{
		if (texture == nullptr)
			return false;
		App->textures->Unload(texture);

		if (animation != nullptr)
			App->animation->UnregisterAnimation(animation);

		return true;
	}

	bool Update()
	{
		if (texture == nullptr || GetEntity() == nullptr)
			return false;

		// Determina la posición y rotación de la imagen en pantalla
		fPoint temp = offset;
		fPoint renderPosition = GetEntity()->transform->GetGlobalPosition();
		renderPosition += temp.Rotate(GetEntity()->transform->GetGlobalRotation());
		float renderRotation = GetEntity()->transform->GetGlobalRotation() + rotation;
		
		// Determina el frame que pintar
		SDL_Rect* renderArea = NULL;
		if (animation != nullptr)
			renderArea = &(animation->GetCurrentFrame());

		App->renderer->Blit(texture, (int)renderPosition.x, (int)renderPosition.y, renderRotation, NULL, renderArea);

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
