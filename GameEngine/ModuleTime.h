#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Globals.h"

class ModuleTime : public Module
{
public:
	ModuleTime(bool start_enabled = true);
	~ModuleTime();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	float DeltaTime();

private:
	unsigned long lastFrameTime;
	float deltaTime;
};

#endif // __MODULETIME_H__