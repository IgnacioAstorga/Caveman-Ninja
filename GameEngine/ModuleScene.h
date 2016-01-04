#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Globals.h"

#include <list>

class Scene;

using namespace std;

class ModuleScene : public Module
{
	friend class Application;

public:
	ModuleScene();
	virtual ~ModuleScene();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void ChangeScene(Scene* scene);
	void DestroyScene(Scene* scene);

	Scene* GetCurrentScene();

private:
	Scene* currentScene;
	Scene* nextScene;
	list<Scene*> toDestroy;

	void DoChangeScene();
};
#endif // __MODULESCENE_H__