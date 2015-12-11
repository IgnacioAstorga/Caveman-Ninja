#ifndef __SPRITERENDERER_H__
#define __SPRITERENDERER_H__

#include "ParticleRenderer.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "SDL.h"

using namespace std;

class SpriteRenderer : public ParticleRenderer
{
public:
	SpriteRenderer(string textureName)
	{
		this->textureName = textureName;
	}

	bool Start() {
		texture = App->textures->Load(textureName.c_str());

		return true;
	}

	bool CleanUp() {
		App->textures->Unload(texture);

		return true;
	}

	update_status Render(const Particle& particle)
	{
		if (texture == nullptr)
			return UPDATE_ERROR;

		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		App->renderer->Blit(texture, (int) particle.position.x - (w / 2), (int) particle.position.y - (h / 2), NULL, 1.0f);

		return UPDATE_CONTINUE;
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
};

#endif //  __SPRITERENDERER_H__
