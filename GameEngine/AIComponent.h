#ifndef __AICOMPONENT_H__
#define __AICOMPONENT_H__

#include "Component.h"

class AIManager;

class AIComponent : public Component
{
public:
	AIComponent(AIManager* manager, bool start_enabled = true);
	virtual ~AIComponent();

public:
	bool OnStart();
	bool OnCleanUp();

public:
	AIManager* GetAIManager();

private:
	AIManager* manager;
};

#endif //  __AICOMPONENT_H__