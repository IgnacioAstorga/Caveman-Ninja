#ifndef __PLAYERHARVESTEFFECT_H__
#define __PLAYERHARVESTEFFECT_H__

#include "Entity.h"

class PlayerHarvestEffect : public Entity
{
public:
	PlayerHarvestEffect(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~PlayerHarvestEffect() { OnDestroy(); };

protected:
	void OnCreate();
};
#endif	// __PLAYERHARVESTEFFECT_H__