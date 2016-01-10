#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Globals.h"

#include <list>

class Timer;

using namespace std;

class ModuleTime : public Module
{
public:
	ModuleTime(bool start_enabled = true);
	~ModuleTime();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	float DeltaTime();
	void RegisterTimer(Timer* timer);
	void UnregisterTimer(Timer* timer);

private:
	unsigned long lastFrameTime;
	float deltaTime;

	list<Timer*> timers;
};

#endif // __MODULETIME_H__