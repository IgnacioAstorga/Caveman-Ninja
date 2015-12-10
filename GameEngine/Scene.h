#ifndef __SCENE_H__
#define __SCENE_H__

#include "Globals.h"
#include "Entity.h"

#include <list>

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();

private:
	void Create();
	void Destroy();

public:
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	const list<Entity*>& GetChildren();
	Entity* FindChild(string name);
	Entity* FindChild(string name, int deepness);
	template <class T> T* FindChild();
	template <class T> T* FindChild(int deepness);
	list<Entity*> FindAllChildren(string name);
	list<Entity*> FindAllChildren(string name, int deepness);
	template <class T> list<T*> FindAllChildren();
	template <class T> list<T*> FindAllChildren(int deepness);

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

protected:
	virtual void OnCreateScene() {};	// Previo a la inicialización de la escena, utilizar para cargar cosas
	virtual void OnDestroyScene() {};	// Posterior a la descarga de los elementos de la escena, utilizar para borrar cosas

	virtual bool OnSceneStart() { return true; };	// Inicialización de la escena, utilizar para configurar las cosas
	virtual bool OnSceneCleanUp() { return true; };	// Descarga de los elementos de la escena
	virtual update_status OnScenePreUpdate() { return UPDATE_CONTINUE; };
	virtual update_status OnSceneUpdate() { return UPDATE_CONTINUE; };
	virtual update_status OnScenePostUpdate() { return UPDATE_CONTINUE; };

private:
	Entity* root;
};
#endif //__SCENE_H__
