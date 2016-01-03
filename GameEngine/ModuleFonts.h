#ifndef __MODULEFONTS_H__
#define __MODULEFONTS_H__

#include <list>
#include "Module.h"
#include "Globals.h"

#include "SDL_ttf.h"

class ModuleFonts : public Module
{
public:
	ModuleFonts();
	~ModuleFonts();

	bool Init();
	bool CleanUp();

	TTF_Font* const Load(const char* path, unsigned int size);
	void Unload(TTF_Font* font);

private:
	std::list<TTF_Font*> fonts;
};

#endif // __MODULEFONTS_H__