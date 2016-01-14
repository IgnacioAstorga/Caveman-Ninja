#ifndef __FANGPROJECTILE_H__
#define __FANGPROJECTILE_H__

#include "Entity.h"

class FangProjectile : public Entity
{
public:
	FangProjectile(bool up, std::string name, float positionX = 0.0f, float positionY = 0.0f);
	~FangProjectile() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

private:
	bool up;
};
#endif	// __FANGPROJECTILE_H__