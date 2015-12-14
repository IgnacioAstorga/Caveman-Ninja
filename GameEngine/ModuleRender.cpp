#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL.h"
#include "Camera.h"
#include "Transform.h"

ModuleRender::ModuleRender()
{
	// En principio no hace nada
}

// Destructor
ModuleRender::~ModuleRender()
{
	LOG("Destroying renderer");

	// Destroy window
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

void ModuleRender::SetActiveCamera(Camera* camera)
{
	if (activeCamera != nullptr)
		activeCamera->active = false;

	if (camera != nullptr)
		camera->active = true;

	activeCamera = camera;
}

Camera* ModuleRender::GetActiveCamera()
{
	return activeCamera;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, fPoint scale, float speed)
{
	return Blit(texture, x, y, 0.0, NULL, NULL, section, scale, speed);
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, double angle, SDL_Point* pivot, SDL_Rect* section, fPoint scale, float speed)
{
	return Blit(texture, x, y, angle, pivot, NULL, section, scale, speed);
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, double angle, SDL_Point* pivot, SDL_Color* color, SDL_Rect* section, fPoint scale, float speed)
{
	if (activeCamera == nullptr)
		return false;

	bool ret = true;
	SDL_Rect cameraView = activeCamera->GetViewArea();
	SDL_Rect rect;
	rect.x = (int)((-cameraView.x * speed + x * SCREEN_SIZE) * (float)App->window->screen_surface->w / (float)cameraView.w);	// La posición de la cámara debe ser negativa
	rect.y = (int)((-cameraView.y * speed + y * SCREEN_SIZE) * (float)App->window->screen_surface->h / (float)cameraView.h);	// El desplazamiento se realiza en proporción a la camara

	// Determina el área donde pintar en función de la escala
	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}
	rect.w = (int)(rect.w * scale.x * SCREEN_SIZE);
	rect.h = (int)(rect.h * scale.y * SCREEN_SIZE);

	// Reescala el área la imagen para ajustarse a la cámara
	rect.w = (int)((float)rect.w * (float)App->window->screen_surface->w / (float)cameraView.w);
	rect.h = (int)((float)rect.h * (float)App->window->screen_surface->h / (float)cameraView.h);
	
	// Determina el color de la textura
	if (color != NULL && SDL_SetTextureColorMod(texture, color->r, color->g, color->b))
	{
		LOG("Cannot tint texture. SDL_SetTextureColorMod error: %s", SDL_GetError());
		ret = false;
	}

	// Determina la transparencia de la textura
	if (color != NULL && SDL_SetTextureAlphaMod(texture, color->a))
	{
		LOG("Cannot change texture opacity. SDL_SetTextureAlphaMod error: %s", SDL_GetError());
		ret = false;
	}

	// Renderiza la textura
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, pivot, SDL_RendererFlip()) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopyEx error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}