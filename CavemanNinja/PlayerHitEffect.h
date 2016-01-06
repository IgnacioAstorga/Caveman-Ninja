#ifndef __PLAYERHITEFFECT_H__
#define __PLAYERHITEFFECT_H__

#include "Entity.h"

class PlayerHitEffect : public Entity
{
public:
	PlayerHitEffect(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~PlayerHitEffect() { OnDestroy(); };

protected:
	void OnCreate();
};
#endif	// __PLAYERHITEFFECT_H__