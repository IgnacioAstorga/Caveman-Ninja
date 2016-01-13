#ifndef __ENEMYHITEFFECT_H__
#define __ENEMYHITEFFECT_H__

#include "Entity.h"

class EnemyHitEffect : public Entity
{
public:
	EnemyHitEffect(std::string name, bool big = false, float positionX = 0.0f, float positionY = 0.0f);
	~EnemyHitEffect();

protected:
	void OnCreate();

public:
	bool big;
};
#endif	// __ENEMYHITEFFECT_H__