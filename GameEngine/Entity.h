#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Globals.h"

#include <list>

class Component;
class Transform;
class Scene;

using namespace std;

class Entity
{
public:
	Entity(string name, float x = 0.0f, float y = 0.0f, bool start_enabled = true);
	virtual ~Entity();

public:
	Entity* Instantiate(Scene* scene);		// Instantiate se debe llamar solo cuando se crea una entidad durante el juego
	Entity* Instantiate(Entity* parent);	// En la preparación de la escena o para cambiar el padre de la entidad, utilizar los métodos AddChild/SetParent de la escena/entidad padre
	void Destroy();

public:
	bool IsEnabled();
	bool Enable();
	bool Disable();

	Entity* GetParent();
	void SetParent(Entity* entity);
	void SetParent(Scene* scene);

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

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	const list<Component*>& GetComponents();
	template <class T> T* FindComponent();
	template <class T> list<T*> FindAllComponents();

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

protected:
	virtual void OnCreate() {};
	virtual void OnDestroy() {};

	virtual bool OnStart() { return true; };
	virtual bool OnCleanUp() { return true; };

public:
	string name;
	Transform* transform;

private:
	bool started;
	bool enabled;
	bool dead;
	Entity* parent;
	Scene* scene;
	list<Entity*> children;
	list<Component*> components;
};
#endif //__ENTITY_H__
