#ifndef __EGG_H__
#define __EGG_H__

#include "Entity.h"

class Egg : public Entity
{
public:
	Egg(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~Egg() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __EGG_H__