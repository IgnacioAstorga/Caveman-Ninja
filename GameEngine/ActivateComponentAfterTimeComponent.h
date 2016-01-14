#ifndef __ACTIVATECOMPONENTAFTERSTARTCOMPONENT_H__
#define __ACTIVATECOMPONENTAFTERSTARTCOMPONENT_H__

#include "Component.h"
#include "Timer.h"

#include <vector>

using namespace std;

class ActivateComponentAfterTimeComponent : public Component
{
public:
	ActivateComponentAfterTimeComponent(float time, Component* component, bool start_enabled = true);
	ActivateComponentAfterTimeComponent(float time, vector<Component*> components, bool start_enabled = true);
	virtual ~ActivateComponentAfterTimeComponent();

protected:
	bool OnStart();
	bool OnCleanUp();
	bool OnPreUpdate();

public:
	float time;
	Timer timer;
	vector<Component*> components;
};

#endif // __ACTIVATECOMPONENTAFTERSTARTCOMPONENT_H__