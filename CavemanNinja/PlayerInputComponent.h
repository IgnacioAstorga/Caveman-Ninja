#ifndef __PLAYERINPUTCOMPONENT_H__
#define __PLAYERINPUTCOMPONENT_H__

#include "Component.h"

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(float speed);
	virtual ~PlayerInputComponent();

protected:
	bool OnPreUpdate();

public:
	float speed;
};
#endif //__PLAYERINPUTCOMPONENT_H__