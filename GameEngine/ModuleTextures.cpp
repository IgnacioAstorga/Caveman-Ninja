#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL.h"

#include "SDL_image.h"
#pragma comment( lib, "SDL2_image.lib" )

using namespace std;

ModuleTextures::ModuleTextures()
{
}

ModuleTextures::~ModuleTextures()
{
	IMG_Quit();
}

bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for(unordered_map<string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(it->second);
	textures.clear();

	return true;
}

SDL_Texture* const ModuleTextures::Load(const char* path)
{
	// Comprueba si la textura ya existe
	if (textures[path] != nullptr)
	{
		textureUseCount[path] += 1;
		return textures[path];
	}

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures[path] = texture;
			textureUseCount[path] = 1;
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

void ModuleTextures::Unload(SDL_Texture* texture)
{
	for(unordered_map<string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if(it->second == texture)
		{
			textureUseCount[it->first] -= 1;
			if (textureUseCount[it->first] <= 0)
			{
				SDL_DestroyTexture(it->second);
				textures[it->first] = nullptr;
				break;
			}
		}
	}
}