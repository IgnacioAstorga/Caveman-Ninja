#ifndef __SPRITERENDERER_H__
#define __SPRITERENDERER_H__

#include "ParticleRenderer.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Transform.h"
#include "Animation.h"
#include "ModuleAnimation.h"

#include "SDL.h"

using namespace std;

class SpriteRenderer : public ParticleRenderer
{
public:
	SpriteRenderer(string textureName)
	{
		this->textureName = textureName;
		animation = nullptr;
	}

	SpriteRenderer(string textureName, Animation* animation)
	{
		this->textureName = textureName;
		this->animation = animation;
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

	update_status Render(const Particle& particle)
	{
		if (texture == nullptr)
			return UPDATE_ERROR;

		// Determina la posición y rotación de la partícula en pantalla
		fPoint temp = particle.position;
		fPoint renderPosition = system->GetTransform()->GetGlobalPosition();
		renderPosition += temp.Rotate(system->GetTransform()->GetGlobalRotation());
		float renderRotation = system->GetTransform()->GetGlobalRotation() + particle.rotation;

		// Determina el color y opacidad de la partícula
		SDL_Color renderColor;
		renderColor.r = (unsigned int)(particle.tint.red * 255);
		renderColor.g = (unsigned int)(particle.tint.green * 255);
		renderColor.b = (unsigned int)(particle.tint.blue * 255);
		renderColor.a = (unsigned int)(particle.tint.alpha * 255);

		// Determina el frame que pintar
		SDL_Rect* renderArea = NULL;
		int width, height;
		if (animation != nullptr)
		{
			renderArea = &(animation->GetCurrentFrame());
			width = renderArea->w;
			height = renderArea->h;
		}
		else
			SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		App->renderer->Blit(texture, (int)(renderPosition.x - (width / 2)), (int)(renderPosition.y - (height / 2)), renderRotation, NULL, &renderColor, renderArea);

		return UPDATE_CONTINUE;
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
};

#endif //  __SPRITERENDERER_H__
