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
	// Inicializa la escena actual
	if (currentScene == nullptr)
		return false;
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
}

bool ModuleScene::CleanUp()
{
	// Llamada al CleanUp de la escena actual
	if (currentScene == nullptr)
		return false;
	return currentScene->CleanUp();
}

void ModuleScene::ChangeScene(Scene* scene)
{
	// Realiza la preparación para cambiar la escena
	nextScene = scene;
}

void ModuleScene::DoChangeScene()
{
	if (nextScene != nullptr) {
		// Elimina la escena anterior (de haberla)
		if (currentScene != nullptr) {
			currentScene->CleanUp();
			RELEASE(currentScene);
		}

		// Realiza el cambio de escena
		currentScene = nextScene;
		nextScene = nullptr;
		currentScene->Start();
	}
}
