#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "CollisionListener.h"
#include "Globals.h"

#include <list>

class Component;
class Transform;
class Scene;

using namespace std;

class Entity : public CollisionListener
{
	friend class Scene;

public:
	Entity(string name, float x = 0.0f, float y = 0.0f, bool start_enabled = true);
	virtual ~Entity();

public:
	Entity* Instantiate();
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
	void RemoveChild(Entity* child, bool attachRoot = true);
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

	bool OnCollisionEnter(Collider* self, Collider* other);
	bool OnCollisionStay(Collider* self, Collider* other);
	bool OnCollisionExit(Collider* self, Collider* other);

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

template<class T>
T* Entity::FindChild()
{
	return FindChild<T>(-1);
}

template<class T>
T* Entity::FindChild(int deepness)
{
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
		if (casted != NULL)
			return casted;
		else if (deepness != 0)
		{
			T* ret = (*it)->FindChild<T>(deepness - 1);
			if (ret != nullptr)
				return ret;
		}
	}
	return nullptr;
}

template<class T>
list<T*> Entity::FindAllChildren()
{
	return FindAllChildren<T>(-1);
}

template<class T>
list<T*> Entity::FindAllChildren(int deepness)
{
	list<T*> allChildren;
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it)
		if (casted != NULL)
			allChildren.push_back(casted);
		if (deepness != 0)
		{
			list<T*> ret = (*it)->FindAllChildren<T>(deepness - 1);
			if (!ret.empty())
				allChildren.insert(allChildren.end(), ret.begin(), ret.end());
		}
	}
	return allChildren;
}

template<class T>
T* Entity::FindComponent()
{
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
		if (casted != NULL)
			return casted;
	}

	return nullptr;
}

template<class T>
list<T*> Entity::FindAllComponents()
{
	list<T*> allComponents;
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
		if (casted != NULL)
			allComponents.push_back(casted);
	}

	return allComponents;
}
#endif //__ENTITY_H__
