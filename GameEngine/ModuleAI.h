#ifndef __MODULEAI_H__
#define __MODULEAI_H__

#include "Module.h"

#include <list>

class AIManager;

using namespace std;

class ModuleAI : public Module
{
public:
	ModuleAI(bool start_enabled = true);
	~ModuleAI();

public:
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	void RegisterAIManager(AIManager* manager);
	void UnregisterAIManager(AIManager* manager);

private:
	list<AIManager*> managers;
};
#endif // __MODULEAI_H__
