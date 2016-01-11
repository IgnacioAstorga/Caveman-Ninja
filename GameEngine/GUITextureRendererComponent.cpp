#include "GUITextureRendererComponent.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Animation.h"
#include "ModuleAnimation.h"
#include "Color.h"

#include "SDL.h"

GUITextureRendererComponent::GUITextureRendererComponent(Animation* animation, float offsetX, float offsetY, GUILocation location, bool shadow, fPoint shadowOffset, bool start_enabled) : GUIComponent(location, start_enabled)
{
	this->animation = animation;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->shadow = shadow;
	this->shadowOffset = shadowOffset;
}

GUITextureRendererComponent::~GUITextureRendererComponent()
{
	RELEASE(animation);
}

bool GUITextureRendererComponent::GUIStart()
{
	texture = OnLoadTexture();
	if (texture == nullptr)
		return false;

	if (animation != nullptr)
		App->animation->RegisterAnimation(animation);

	return true;
}

bool GUITextureRendererComponent::GUICleanUp()
{
	if (texture == nullptr)
		return false;
	App->textures->Unload(texture);

	if (animation != nullptr)
		App->animation->UnregisterAnimation(animation);

	return true;
}

bool GUITextureRendererComponent::GUIPostUpdate()
{
	if (texture == nullptr || entity == nullptr)
		return false;

	// Determina la posición de la imagen en pantalla
	fPoint temp = fPoint(offsetX, offsetY);
	temp.x *= entity->transform->GetGlobalScale().x;
	temp.y *= entity->transform->GetGlobalScale().y;
	fPoint renderPosition = GetReferencePosition();
	renderPosition += temp.Rotate(entity->transform->GetGlobalRotation());

	// Determina la rotación de la imagen en pantalla
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

	// Dibuja la sombra
	if (shadow)
		App->renderer->Blit(texture, (int)(renderPosition.x + shadowOffset.x), (int)(renderPosition.y + shadowOffset.y), renderRotation, &pivot, &BLACK.ToSDLColor(), renderArea, renderScale);

	// Dibuja la imagen
	App->renderer->Blit(texture, (int)renderPosition.x, (int)renderPosition.y, renderRotation, &pivot, &WHITE.ToSDLColor(), renderArea, renderScale);

	return true;
}

fPoint GUITextureRendererComponent::GetReferencePosition()
{
	SDL_Rect viewArea = App->renderer->activeCamera->GetViewArea();
	fPoint origin = fPoint((float)viewArea.x, (float)viewArea.y);
	fPoint position = entity->transform->GetGlobalPosition();

	// Determina la posición adecuada del elemento
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