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
#include "Camera.h"

#include "SDL.h"

using namespace std;

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(string textureName, float rotation = 0.0f)
		: SpriteRendererComponent(textureName, nullptr, 0.0f, 0.0f, rotation) {}

	SpriteRendererComponent(string textureName, Animation* animation, float rotation = 0.0f)
		: SpriteRendererComponent(textureName, animation, 0.0f, 0.0f, rotation) {}

	SpriteRendererComponent(string textureName, Animation* animation, float offsetX, float offsetY, float rotation = 0.0f, float speed = 1.0f, bool tiledHorizontal = false, bool tiledVertical = false, bool start_enabled = true) : Component(start_enabled)
	{
		this->textureName = textureName;
		this->animation = animation;
		offset.x = offsetX;
		offset.y = offsetY;
		this->rotation = rotation;
		this->speed = speed;
		this->tiledHorizontal = tiledHorizontal;
		this->tiledVertical = tiledVertical;
	}

	~SpriteRendererComponent()
	{
		RELEASE(animation);
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

	bool OnCleanUp()
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
		SDL_Point pivot;
		pivot.x = 0;
		pivot.y = 0;

		// Determina la escala de la imagen en pantalla
		fPoint renderScale = entity->transform->GetGlobalScale();

		
		// Determina el frame que pintar
		SDL_Rect* renderArea = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (animation != nullptr)
		{
			flip = animation->GetFlip();
			renderArea = &(animation->GetCurrentFrame());
		}
		else
		{
			renderArea = new SDL_Rect();
			renderArea->x = 0;
			renderArea->y = 0;
			SDL_QueryTexture(texture, NULL, NULL, &renderArea->w, &renderArea->h);
		}

		Render(renderPosition, renderRotation, &pivot, renderArea, renderScale, flip, speed);

		return true;
	}

	virtual void Render(fPoint renderPosition, float renderRotation, SDL_Point* pivot, SDL_Rect* renderArea, fPoint renderScale, SDL_RendererFlip flip, float speed)
	{
		if (!tiledHorizontal && !tiledVertical)
			App->renderer->Blit(texture, (int)renderPosition.x, (int)renderPosition.y, renderRotation, pivot, renderArea, renderScale, flip, speed);
		else
		{
			// Calcula el offset con el que pintar el sprite
			SDL_Rect viewArea = App->renderer->activeCamera->GetViewArea();
			iPoint offsetFactor = iPoint((int)(viewArea.x * speed / renderArea->w), (int)(viewArea.y * speed / renderArea->h));
			iPoint offsetVector = iPoint(renderArea->w * offsetFactor.x, renderArea->h * offsetFactor.y);

			// Renderiza la imagen así como suficientes para llenar la pantalla
			iPoint finalPosition;
			int i = 0;
			bool completedHorizontal = false;
			do
			{
				int j = 0;
				bool completedVertical = false;
				do
				{

					// Calcula la posición y pinta (barrido en horizontal)
					finalPosition = iPoint((int)renderPosition.x, (int)renderPosition.y);
					if (tiledHorizontal)
					{
						finalPosition.x += offsetVector.x;
						finalPosition.x += i * renderArea->w;
					}
					if (tiledVertical)
					{
						finalPosition.y += offsetVector.y;
						finalPosition.y += j * renderArea->h;
					}
					App->renderer->Blit(texture, finalPosition.x, finalPosition.y, renderRotation, pivot, renderArea, renderScale, flip, speed);

					if (!tiledVertical)
						break;

					if (j >= 0)
						if (finalPosition.y < (viewArea.y + viewArea.h))
							j++; // Pinta hacia abajo
						else
							j = -1;	// Empieza a pintar hacia la arriba
					else
						if ((finalPosition.y + renderArea->h) > viewArea.y)
							j--; // Pinta hacia la arriba
						else
							completedVertical = true;	// Finaliza el pintado vertical
				} while (!completedVertical);

				if (!tiledHorizontal)
					break;

				if (i >= 0)
					if (finalPosition.x < (viewArea.x + viewArea.w))
						i++; // Pinta hacia la derecha
					else
						i = -1;	// Empieza a pintar hacia la izquierda
				else
					if ((finalPosition.x + renderArea->w) > viewArea.x)
						i--; // Pinta hacia la izquierda
					else
						completedHorizontal = true;	// Finaliza el pintado
			} while (!completedHorizontal);
		}
	}


	Animation* GetAnimation() {
		return animation;
	}

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	fPoint offset;
	float rotation;
	float speed;
	bool tiledHorizontal;
	bool tiledVertical;
};

#endif //  __SPRITERENDERERCOMPONENT_H__
