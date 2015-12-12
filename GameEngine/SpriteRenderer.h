#ifndef __SPRITERENDERER_H__
#define __SPRITERENDERER_H__

#include "ParticleRenderer.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Transform.h"

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

		// Pinta la partícula
		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		App->renderer->Blit(texture, (int)(renderPosition.x - (w / 2)), (int)(renderPosition.y - (h / 2)), renderRotation, NULL, &renderColor);

		return UPDATE_CONTINUE;
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
};

#endif //  __SPRITERENDERER_H__
