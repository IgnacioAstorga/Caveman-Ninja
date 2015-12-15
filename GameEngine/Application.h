#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include <list>

#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleTime;
class ModuleAnimation;
class ModuleParticles;
class ModuleScene;
class ModuleCollisions;

class Scene;

class Application
{
public:
	Application();
	~Application();
	int Run();

private:
	void Create();

public:
	bool Init();
	update_status Update();
	bool CleanUp();

protected:
	virtual void OnCreateApplication() {};
	virtual void OnDestroyApplication() {};

	virtual Scene* OnCreateScene() = 0;	// Crea y devuelve la escena inicial
	virtual bool OnPopulateScene(Scene* scene) { return true; };	// Llamado tras arrancar la escena inicial

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleTime* time;
	ModuleAnimation* animation;
	ModuleParticles* particles;
	ModuleScene* scene;
	ModuleCollisions* collisions;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__