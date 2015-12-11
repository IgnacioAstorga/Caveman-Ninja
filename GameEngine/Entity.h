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
	virtual void OnCreate() {};
	virtual void OnDestroy() {};

	virtual bool OnStart() { return true; };
	virtual bool OnCleanUp() { return true; };

public:
	string name;

private:
	bool enabled;
	bool dead;
	Entity* parent;
	list<Entity*> children;
};
#endif //__ENTITY_H__
