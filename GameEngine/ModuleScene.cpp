#include "Globals.h"
#include "ModuleScene.h"
#include "Scene.h"

ModuleScene::ModuleScene()
{
	nextScene = nullptr;
}

ModuleScene::~ModuleScene()
{
	// Destruye la escena actual
	RELEASE(currentScene)
}

bool ModuleScene::Start()
{
	LOG("Starting scene");

	// Inicializa la escena actual
	if (currentScene == nullptr)
	{
		LOG("No starting scene declarated!")
		return false;
	}
	return currentScene->Start();
}

update_status ModuleScene::PreUpdate()
{
	// Antes de nada, realiza el cambio de escena
	if (nextScene != nullptr)
		DoChangeScene();

	// Llamada al PreUpdate de la escena actual
	if (currentScene == nullptr)
		return UPDATE_ERROR;
	return currentScene->PreUpdate();
}

update_status ModuleScene::Update()
{
	// Llamada al Update de la escena actual
	if (currentScene == nullptr)
		return UPDATE_ERROR;
	return currentScene->Update();
}

update_status ModuleScene::PostUpdate()
{
	// Llamada al PostUpdate de la escena actual
	if (currentScene == nullptr)
		return UPDATE_ERROR;
	return currentScene->PostUpdate();

	// Finalmente, elimina las escenas pendientes de morir
	for (list<Scene*>::iterator it = toDestroy.begin(); it != toDestroy.end(); ++it)
		RELEASE(*it);
	toDestroy.clear();
}

bool ModuleScene::CleanUp()
{
	LOG("Cleaning scene");

	// Llamada al CleanUp de la escena actual
	if (currentScene == nullptr)
		return false;
	return currentScene->CleanUp();
}

void ModuleScene::ChangeScene(Scene* scene)
{
	LOG("Setup for scene change");

	// Realiza la preparación para cambiar la escena
	nextScene = scene;
}

void ModuleScene::DestroyScene(Scene* scene)
{
	// Marca la escena para morir
	toDestroy.push_back(scene);
}

Scene * ModuleScene::GetCurrentScene()
{
	return currentScene;
}

void ModuleScene::DoChangeScene()
{
	LOG("Changing current scene");

	if (nextScene != nullptr) {
		// Elimina la escena anterior (de haberla)
		if (currentScene != nullptr)
			currentScene->CleanUp();

		// Realiza el cambio de escena
		currentScene = nextScene;
		nextScene = nullptr;
		currentScene->Start();
	}
}
