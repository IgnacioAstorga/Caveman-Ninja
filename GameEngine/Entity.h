#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Globals.h"

#include <list>

using namespace std;

class Entity
{
public:
	Entity();
	virtual ~Entity();

private:
	void Create();
	void Destroy();

public:
	bool IsEnabled();
	bool Enable();
	bool Disable();

	Entity* GetParent();
	void SetParent(Entity* entity);

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
	virtual void OnCreate() {};	// Previo a la inicialización de la entidad, utilizar para cargar cosas
	virtual void OnDestroy() {};	// Posterior a la descarga de los elementos de la entidad, utilizar para borrar cosas

	virtual bool OnStart() { return true; };	// Inicialización de la escena, utilizar para configurar las cosas
	virtual bool OnCleanUp() { return true; };	// Descarga de los elementos de la escena
	virtual update_status OnPreUpdate() { return UPDATE_CONTINUE; };
	virtual update_status OnUpdate() { return UPDATE_CONTINUE; };
	virtual update_status OnPostUpdate() { return UPDATE_CONTINUE; };

public:
	string name;

private:
	bool enabled;
	Entity* parent;
	list<Entity*> children;
};
#endif //__ENTITY_H__
