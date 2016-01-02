#include "ModuleFonts.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"

using namespace std;

ModuleFonts::ModuleFonts()
{
	// En principio no hace nada
}

ModuleFonts::~ModuleFonts()
{
	TTF_Quit();
}

bool ModuleFonts::Init()
{
	LOG("Init Font library");

	if (TTF_Init() < 0)
	{
		LOG("Could not initialize Font lib. TTF_Init: %s", TTF_GetError());
		return false;
	}

	return true;
}

bool ModuleFonts::CleanUp()
{
	LOG("Freeing fonts");

	for (list<TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
		TTF_CloseFont(*it);
	fonts.clear();

	return true;
}

TTF_Font* const ModuleFonts::Load(const char* path, unsigned int size)
{
	TTF_Font* font = TTF_OpenFont(path, size);

	if (font == nullptr)
	{
		LOG("Could not load font with path: %s. IMG_Load: %s", path, TTF_GetError());
	}
	else
	{
		fonts.push_back(font);
	}

	return font;
}

void ModuleFonts::Unload(TTF_Font* font)
{
	for (list<TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
	{
		if (*it == font)
		{
			TTF_CloseFont(*it);
			fonts.remove(*it);
			break;
		}
	}
}