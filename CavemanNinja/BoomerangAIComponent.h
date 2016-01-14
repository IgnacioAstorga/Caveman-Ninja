#ifndef __BOOMERANGAICOMPONENT_H__
#define __BOOMERANGAICOMPONENT_H__

#include "Component.h"
#include "Timer.h"

class BoomerangAIComponent : public Component
{
public:
	BoomerangAIComponent(float returnTime);
	virtual ~BoomerangAIComponent();

protected:
	bool OnStart();
	bool OnCleanUp();
	bool OnUpdate();

public:
	float returnTime;
	Timer timer;
	bool returning;

	float speed;
};
#endif // __BOOMERANGAICOMPONENT_H__