#ifndef __TOMAHAWKBIGPROJECTILE_H__
#define __TOMAHAWKBIGPROJECTILE_H__

#include "Entity.h"

class TomahawkBigProjectile : public Entity
{
public:
	TomahawkBigProjectile(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };
	~TomahawkBigProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __TOMAHAWKBIGPROJECTILE_H__