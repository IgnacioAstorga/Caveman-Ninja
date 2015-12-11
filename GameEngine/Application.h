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
class ModuleParticles;
class ModuleScene;

class Scene;

class Application
{
public:
	Application();
	~Application();
	int Run();

private:
	void Create();
	void Destroy();

public:
	bool Init();
	update_status Update();
	bool CleanUp();

protected:
	virtual void OnCreateApplication() {};
	virtual void OnDestroyApplication() {};

	virtual bool OnApplicationInit() { return true; };	// Previo a la inicialización (cambiar la configuración aquí)
	virtual bool OnApplicationStart() { return true; };	// Previo a que los módulos se inicien (cargar la escena aquí)
	virtual update_status OnApplicationUpdate() { return UPDATE_CONTINUE; };	// Previo a cada update del juego
	virtual bool OnApplicationCleanUp() { return true; };	// Previo a la limpieza de la aplicación (guardar datos aquí)

	virtual Scene* OnCreateScene() = 0;

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleTime* time;
	ModuleParticles* particles;
	ModuleScene* scene;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__