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

	void Destroy();

public:
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);

	const list<Entity*>& GetChildren() const;

	Entity* FindChild(string name) const;
	Entity* FindChild(string name, int deepness) const;
	template <class T> T* FindChild() const;
	template <class T> T* FindChild(int deepness) const;
	list<Entity*> FindAllChildren(string name) const;
	list<Entity*> FindAllChildren(string name, int deepness) const;
	template <class T> list<T*> FindAllChildren() const;
	template <class T> list<T*> FindAllChildren(int deepness) const;

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

protected:
	virtual void OnCreateScene() {};	// Previo a la inicialización de la escena, utilizar para cargar cosas
	virtual void OnDestroyScene() {};	// Posterior a la descarga de los elementos de la escena, utilizar para borrar cosas

	virtual bool OnSceneStart() { return true; };	// Inicialización de la escena, utilizar para llenar la escena y configurar cosas
	virtual bool OnSceneCleanUp() { return true; };	// Descarga de la escena, utilizar para eliminar las cosas creadas en OnSceneStart

private:
	Entity* root;
};
#endif //__SCENE_H__
