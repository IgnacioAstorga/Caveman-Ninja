#ifndef __ROLLINGBALL_H__
#define __ROLLINGBALL_H__

#include "Entity.h"

class RollingBall : public Entity
{
public:
	RollingBall(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~RollingBall() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __ROLLINGBOULDER_H__