#ifndef __TOMAHAWKPROJECTILE_H__
#define __TOMAHAWKPROJECTILE_H__

#include "Entity.h"

class TomahawkProjectile : public Entity
{
public:
	TomahawkProjectile(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };
	~TomahawkProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __TOMAHAWKPROJECTILE_H__