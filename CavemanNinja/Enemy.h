#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) {};
	virtual ~Enemy() {};

public:
	void Kill();
};
#endif	// __ENEMY_H__