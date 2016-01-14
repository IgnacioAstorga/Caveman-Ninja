#include "GameControllerComponent.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTime.h"
#include "ModuleCollisions.h"
#include "Scene_Level1.h"
#include "Player.h"
#include "PlayerInputComponent.h"
#include "Enemy.h"
#include "Transform.h"
#include "Collider.h"
#include "ColliderTypes.h"
#include "PlayerLifeComponent.h"

#define RESTART_DELAY 8.0f

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
	// Carga los efectos de sonido y reproduce la música
	victorySound = App->audio->LoadFx("assets/sounds/victory.wav");
	App->audio->PlayMusic("assets/sounds/world_1_music.mp3");

	// Establece la puntuación a cero
	score = 0;
	victory = 0;

	// Registra el timer
	App->time->RegisterTimer(&victoryTimer);

	return true;
}

bool GameControllerComponent::OnCleanUp()
{
	// Desregistra el timer
	App->time->UnregisterTimer(&victoryTimer);

	return true;
}

bool GameControllerComponent::OnPreUpdate()
{
	// Cambia entre modo con y sin modo debug
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		DEBUG = !DEBUG;

	// Activa o desactiva el audio
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		if (App->audio->IsEnabled())
			App->audio->Disable();
		else
			App->audio->Enable();
	}

	// Comprueba si el timer ha expirado
	if (victory && victoryTimer.IsTimerExpired())
		GameOver();

	return true;
}

bool GameControllerComponent::OnCollisionEnter(Collider * self, Collider * other)
{
	if (other->GetType() == PLAYER)
		Win();

	return true;
}

void GameControllerComponent::AddScore(int amount)
{
	score += amount;
}

void GameControllerComponent::GameOver()
{
	// Se limita a reiniciar la escena
	App->scene->ChangeScene(new Scene_Level1());
}

void GameControllerComponent::Win()
{
	// Detiene el jugador
	player->transform->speed.x = 0;
	player->FindComponent<PlayerInputComponent>()->Stop(10.0f);	// Suficiente tiempo

	// Desactiva el componente de vida del jugador
	player->FindComponent<PlayerLifeComponent>()->Disable();

	// Reproduce el sonido y para la música
	App->audio->PauseMusic();
	App->audio->PlayFx(victorySound, 0);	// Canal reservado 0

	// Mata a todos los enemigos
	list<Enemy*> enemies = App->scene->GetCurrentScene()->FindAllChildren<Enemy>();
	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		(*it)->Kill();

	// Activa el timer
	victoryTimer.SetTimer(RESTART_DELAY);
	victory = true;
}
