#ifndef __MOVEMENTSIMPLECOMPONENT_H__
#define __MOVEMENTSIMPLECOMPONENT_H__

#include "Component.h"

class MovementSimpleComponent : public Component
{
public:
	MovementSimpleComponent(bool start_enabled = true);
	virtual ~MovementSimpleComponent();

	bool OnUpdate();
};

#endif // __MOVEMENTSIMPLECOMPONENT_H__