#ifndef __FLYINGDINOSAUR_H__
#define __FLYINGDINOSAUR_H__

#include "Enemy.h"

class FlyingDinosaur : public Enemy
{
public:
	FlyingDinosaur(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Enemy(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~FlyingDinosaur() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __FLYINGDINOSAUR_H__