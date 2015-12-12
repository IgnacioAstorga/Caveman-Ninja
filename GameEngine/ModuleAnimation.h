#ifndef __MODULEANIMATION_H__
#define __MODULEANIMATION_H__

#include "Module.h"

#include <list>

class Animation;

using namespace std;

class ModuleAnimation : public Module
{
public:
	ModuleAnimation(bool start_enabled = true);
	~ModuleAnimation();

public:
	bool Start();
	update_status PostUpdate();
	bool CleanUp();

public:
	void RegisterAnimation(Animation* animation);
	void UnregisterAnimation(Animation* animation);

private:
	list<Animation*> animations;
};
#endif // __MODULEANIMATION_H__
