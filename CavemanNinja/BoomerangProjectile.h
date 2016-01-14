#ifndef __BOOMERANGPROJECTILE_H__
#define __BOOMERANGPROJECTILE_H__

#include "Entity.h"

class BoomerangProjectile : public Entity
{
public:
	BoomerangProjectile(std::string name, float positionX = 0.0f, float positionY = 0.0f);
	~BoomerangProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __BOOMERANGPROJECTILE_H__