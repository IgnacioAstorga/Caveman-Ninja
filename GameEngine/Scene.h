#ifndef __SCENE_H__
#define __SCENE_H__

#include "Globals.h"

#include <list>

class Entity;

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Create();
	void Destroy();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void AddChild(Entity& child);
	void RemoveChild(Entity& child);
	const list<Entity*> GetChildren();
	Entity* FindChild(string name);
	//template <class T> T* FindChild();
	list<Entity*> FindAllChildren(string name);
	//template <class T> list<T*> FindAllChildren();

protected:
	virtual void OnCreateScene();
	virtual void OnDestroyScene();

	virtual void OnSceneStart();
	virtual void OnSceneClean();
	virtual void OnScenePreUpdate();
	virtual void OnSceneUpdate();
	virtual void OnScenePostUpdate();

private:
	list<Entity*> children;
};
#endif //__SCENE_H__