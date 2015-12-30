#ifndef __CAMERAMOVEMENTCOMPONENT_H__
#define __CAMERAMOVEMENTCOMPONENT_H__

#include "Component.h"
#include "ColliderTypes.h"

class Player;

class CameraMovementComponent : public Component
{
public:
	CameraMovementComponent();
	virtual ~CameraMovementComponent();

protected:
	bool OnStart();
	bool OnUpdate();

public:
	Player* player;
};
#endif //__CAMERAMOVEMENTCOMPONENT_H__