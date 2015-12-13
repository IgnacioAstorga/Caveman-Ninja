#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL.h"

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

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

// Called every draw update
update_status ModuleRender::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
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
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

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