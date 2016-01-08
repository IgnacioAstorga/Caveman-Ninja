#ifndef __DINOSAUREYECOMPONENT_H__
#define __DINOSAUREYECOMPONENT_H__

#include "Component.h"

class DinosaurEyeComponent : public Component
{
public:
	DinosaurEyeComponent();
	~DinosaurEyeComponent();

protected:
	bool OnUpdate();
};
#endif	// __DINOSAUREYECOMPONENT_H__