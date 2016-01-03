#ifndef __GAMECONTROLLERCOMPONENT_H__
#define __GAMECONTROLLERCOMPONENT_H__

#include "Component.h"

class GameControllerComponent : public Component
{
public:
	GameControllerComponent();
	~GameControllerComponent();

protected:
	bool OnStart();

public:
	unsigned int music;
};
#endif // __GAMECONTROLLERCOMPONENT_H__