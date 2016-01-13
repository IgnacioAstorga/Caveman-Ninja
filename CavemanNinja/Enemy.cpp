#include "Enemy.h"
#include "DieOnPlayerAttackComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"

void Enemy::Kill()
{
	// Mata al personaje directamente
	FindComponent<DieOnPlayerAttackComponent>()->Die(GameController->player->transform);
}
