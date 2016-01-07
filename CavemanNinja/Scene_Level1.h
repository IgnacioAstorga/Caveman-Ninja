#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Scene.h"

class Scene_Level1 : public Scene
{
public:
	Scene_Level1() { OnCreateScene(); };	// Chapuza: C++ no soporta delegados en los constructores
	~Scene_Level1() { OnDestroyScene(); };

protected:
	void OnCreateScene();
	void OnDestroyScene();

private:
	Entity* camera;
	Entity* ground;
	Entity* gameController;
	Entity* backgroundSky;
	Entity* backgroundMountains;
	Entity* backgroundTrees;
	Entity* gui;
	Entity* player;
};
#endif	// __SCENE_LEVEL1_H__