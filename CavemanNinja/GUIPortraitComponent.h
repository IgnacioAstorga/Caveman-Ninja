#ifndef __GUIPORTRAITCOMPONENT_H__
#define __GUIPORTRAITCOMPONENT_H__

#include "Component.h"

#include <vector>

class PlayerLifeComponent;
class Animator;

enum PortraitStatus {
	IDLE,
	EAT,
	HAPPY,
	HIT,
	DEAD
};

class GUIPortraitComponent : public Component
{
public:
	GUIPortraitComponent();
	virtual ~GUIPortraitComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	PlayerLifeComponent* lifeComponent;
	Animator* animator;
};
#endif //__GUIPORTRAITCOMPONENT_H__