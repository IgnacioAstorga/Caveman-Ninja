#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = NULL, fPoint scale = fPoint(1.0f, 1.0f), float speed = 1.0f);
	bool Blit(SDL_Texture* texture, int x, int y, double angle, SDL_Point* pivot, SDL_Rect* section = NULL, fPoint scale = fPoint(1.0f, 1.0f), float speed = 1.0f);
	bool Blit(SDL_Texture* texture, int x, int y, double angle, SDL_Point* pivot, SDL_Color* color, SDL_Rect* section = NULL, fPoint scale = fPoint(1.0f, 1.0f), float speed = 1.0f);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MODULERENDER_H__