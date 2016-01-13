#ifndef __ENEMYCAVEMAN_H__
#define __ENEMYCAVEMAN_H__

#include "Enemy.h"

class EnemyCaveman : public Enemy
{
public:
	EnemyCaveman(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Enemy(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~EnemyCaveman() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __ENEMYCAVEMAN_H__