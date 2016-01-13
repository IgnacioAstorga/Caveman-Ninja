#ifndef __SPRITEPARTICLERENDERER_H__
#define __SPRITEPARTICLERENDERER_H__

#include "ParticleRenderer.h"
#include "SDL.h"

#include <string>

class Animation;

using namespace std;

class SpriteParticleRenderer : public ParticleRenderer
{
public:
	SpriteParticleRenderer(string textureName, Animation* animation = nullptr);
	~SpriteParticleRenderer();

	bool Start();
	bool CleanUp();

	update_status Render(const Particle& particle);

private:
	string textureName;
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
};

#endif //  __SPRITEPARTICLERENDERER_H__
