#ifndef __USERINTERFACECOMPONENT_H__
#define __USERINTERFACECOMPONENT_H__

#include "Component.h"

class Entity;

class UserInterfaceComponent : public Component
{
public:
	UserInterfaceComponent() {};
	virtual ~UserInterfaceComponent() {};

protected:
	bool OnStart();

public:
	Entity* lifebar;
};
#endif	// __USERINTERFACECOMPONENT_H__