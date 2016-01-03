#include "GameControllerComponent.h"
#include "Application.h"
#include "ModuleAudio.h"

GameControllerComponent::GameControllerComponent()
{
	// En principio no hace nada
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
