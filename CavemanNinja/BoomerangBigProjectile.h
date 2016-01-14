#ifndef __BOOMERANGBIGPROJECTILE_H__
#define __BOOMERANGBIGPROJECTILE_H__

#include "Entity.h"

class BoomerangBigProjectile : public Entity
{
public:
	BoomerangBigProjectile(std::string name, float positionX = 0.0f, float positionY = 0.0f);
	~BoomerangBigProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __BOOMERANGBIGPROJECTILE_H__