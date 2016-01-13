#include "SpriteParticleRenderer.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Transform.h"
#include "Animation.h"
#include "ModuleAnimation.h"
#include "ParticleSystem.h"

SpriteParticleRenderer::SpriteParticleRenderer(string textureName, Animation* animation)
{
	this->textureName = textureName;
	this->animation = animation;
}

SpriteParticleRenderer::~SpriteParticleRenderer()
{
	RELEASE(animation);
}

bool SpriteParticleRenderer::Start()
{
	texture = App->textures->Load(textureName.c_str());
	if (texture == nullptr)
		return false;

	if (animation != nullptr)
		App->animation->RegisterAnimation(animation);

	return true;
}

bool SpriteParticleRenderer::CleanUp()
{
	if (texture == nullptr)
		return false;
	App->textures->Unload(texture);

	if (animation != nullptr)
		App->animation->UnregisterAnimation(animation);

	return true;
}

update_status SpriteParticleRenderer::Render(const Particle& particle)
{
	if (texture == nullptr)
		return UPDATE_ERROR;

	// Determina la posición de la partícula en pantalla
	fPoint renderPosition = system->transform->GetGlobalPosition();
	fPoint offset = particle.position;
	offset.x *= system->transform->GetGlobalScale().x;
	offset.y *= system->transform->GetGlobalScale().y;
	renderPosition += offset.Rotate(system->transform->GetGlobalRotation());

	// Determina la escala de la partícula
	fPoint renderScale = particle.scale;
	renderScale.x *= system->transform->GetGlobalScale().x;
	renderScale.y *= system->transform->GetGlobalScale().y;

	// Determina la rotación de la partícula en pantalla
	float renderRotation = system->transform->GetGlobalRotation() + particle.rotation;

	// Determina el color y opacidad de la partícula
	SDL_Color renderColor = particle.tint.ToSDLColor();

	// Determina el frame que pintar
	SDL_Rect* renderArea = NULL;
	int width, height;
	SDL_RendererFlip flip;
	if (animation != nullptr)
	{
		renderArea = &(animation->GetCurrentFrame());
		width = renderArea->w;
		height = renderArea->h;
		flip = animation->GetFlip();
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		flip = SDL_FLIP_NONE;
	}
	width = (int)(width * renderScale.x);
	height = (int)(height * renderScale.y);

	App->renderer->Blit(texture, (int)(renderPosition.x - (width / 2)), (int)(renderPosition.y - (height / 2)), renderRotation, NULL, &renderColor, renderArea, renderScale, flip);

	return UPDATE_CONTINUE;
}
