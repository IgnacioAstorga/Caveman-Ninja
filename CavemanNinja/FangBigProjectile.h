#ifndef __FANGBIGPROJECTILE_H__
#define __FANGBIGPROJECTILE_H__

#include "Entity.h"

class FangBigProjectile : public Entity
{
public:
	FangBigProjectile(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };
	~FangBigProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __FANGBIGPROJECTILE_H__