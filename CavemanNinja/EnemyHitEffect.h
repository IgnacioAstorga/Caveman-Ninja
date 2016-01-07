#ifndef __ENEMYHITEFFECT_H__
#define __ENEMYHITEFFECT_H__

#include "Entity.h"

class EnemyHitEffect : public Entity
{
public:
	EnemyHitEffect(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~EnemyHitEffect() { OnDestroy(); };

protected:
	void OnCreate();
};
#endif	// __ENEMYHITEFFECT_H__