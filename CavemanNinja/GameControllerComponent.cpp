#include "GameControllerComponent.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "Scene_Level1.h"

GameControllerComponent* GameController = NULL;

GameControllerComponent::GameControllerComponent()
{
	// Se establece globalmente como el GameController
	GameController = this;
}

GameControllerComponent::~GameControllerComponent()
{
	// En principio no hace nada
}

bool GameControllerComponent::OnStart()
{
	// Carga y reproduce la música
	music = App->audio->PlayMusic("assets/sounds/world_1_music.mp3");

	return true;
}

void GameControllerComponent::GameOver()
{
	// Se limita a reiniciar la escena (por ahora)
	App->scene->ChangeScene(new Scene_Level1());
}
