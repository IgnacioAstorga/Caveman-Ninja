#ifndef __GAMECONTROLLERCOMPONENT_H__
#define __GAMECONTROLLERCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class Player;

class GameControllerComponent : public Component
{
public:
	GameControllerComponent();
	~GameControllerComponent();

protected:
	bool OnStart();
	bool OnCleanUp();
	bool OnPreUpdate();

	bool OnCollisionEnter(Collider* self, Collider* other);

public:
	void AddScore(int amount);
	void GameOver();
	void Win();

public:
	int score;
	bool victory;

	Player* player;

	Timer victoryTimer;

	unsigned int victorySound;
};

extern GameControllerComponent* GameController;
#endif // __GAMECONTROLLERCOMPONENT_H__