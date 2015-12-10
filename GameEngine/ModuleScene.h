#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Globals.h"

class Scene;

class ModuleScene : public Module
{

public:
	ModuleScene();
	virtual ~ModuleScene();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void ChangeScene(Scene* scene);

private:
	Scene* currentScene;
	Scene* nextScene;

	void DoChangeScene();
};
#endif // __MODULESCENE_H__