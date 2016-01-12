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
	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	Entity* GetParent() const;
	void SetParent(Entity* entity);
	void SetParent(Scene* scene);

	void AddChild(Entity* child);
	void RemoveChild(Entity* child, bool attachRoot = true);
	const list<Entity*>& GetChildren() const;

	Entity* FindChild(string name) const;
	Entity* FindChild(string name, int deepness) const;
	template <class T> T* FindChild() const;
	template <class T> T* FindChild(int deepness) const;
	list<Entity*> FindAllChildren(string name) const;
	list<Entity*> FindAllChildren(string name, int deepness) const;
	template <class T> list<T*> FindAllChildren() const;
	template <class T> list<T*> FindAllChildren(int deepness) const;

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	const list<Component*>& GetComponents() const;
	template <class T> T* FindComponent() const;
	template <class T> list<T*> FindAllComponents() const;

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
T* Entity::FindChild() const
{
	return FindChild<T>(-1);
}

template<class T>
T* Entity::FindChild(int deepness) const
{
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
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
list<T*> Entity::FindAllChildren() const
{
	return FindAllChildren<T>(-1);
}

template<class T>
list<T*> Entity::FindAllChildren(int deepness) const
{
	list<T*> allChildren;
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
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
T* Entity::FindComponent() const
{
	for (list<Component*>::const_iterator it = components.begin(); it != components.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
		if (casted != NULL)
			return casted;
	}

	return nullptr;
}

template<class T>
list<T*> Entity::FindAllComponents() const
{
	list<T*> allComponents;
	for (list<Component*>::const_iterator it = components.begin(); it != components.end(); ++it)
	{
		T* casted = dynamic_cast<T*>(*it);
		if (casted != NULL)
			allComponents.push_back(casted);
	}

	return allComponents;
}
#endif //__ENTITY_H__
