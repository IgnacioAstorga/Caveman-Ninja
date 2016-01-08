#ifndef __GAMECONTROLLERCOMPONENT_H__
#define __GAMECONTROLLERCOMPONENT_H__

#include "Component.h"

class Player;

class GameControllerComponent : public Component
{
public:
	GameControllerComponent();
	~GameControllerComponent();

protected:
	bool OnStart();
	bool OnPreUpdate();

public:
	void AddScore(int amount);
	void GameOver();

public:
	int score;

	Player* player;

	unsigned int music;
};

extern GameControllerComponent* GameController;
#endif // __GAMECONTROLLERCOMPONENT_H__