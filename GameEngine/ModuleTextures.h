#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Module.h"
#include "Globals.h"

#include <unordered_map>

struct SDL_Texture;

using namespace std;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

private:
	unordered_map<string, SDL_Texture*> textures;
	unordered_map<string, int> textureUseCount;
};

#endif // __MODULETEXTURES_H__