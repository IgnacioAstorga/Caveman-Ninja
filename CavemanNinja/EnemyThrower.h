#ifndef __ENEMYTHROWER_H__
#define __ENEMYTHROWER_H__

#include "Enemy.h"

class EnemyThrower : public Enemy
{
public:
	EnemyThrower(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Enemy(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~EnemyThrower() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __ENEMYTHROWER_H__