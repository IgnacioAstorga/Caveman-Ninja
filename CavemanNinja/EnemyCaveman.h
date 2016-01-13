#ifndef __ENEMYCAVEMAN_H__
#define __ENEMYCAVEMAN_H__

#include "Entity.h"

class EnemyCaveman : public Entity
{
public:
	EnemyCaveman(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~EnemyCaveman() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	void Kill();
};
#endif	// __ENEMYCAVEMAN_H__