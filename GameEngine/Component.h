#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Globals.h"

class Entity;

class Component
{
friend class Entity;

public:
	Component(bool start_enabled = true);
	virtual ~Component();

	Component* Create(Entity* entity);

public:
	bool IsEnabled();
	bool Enable();
	bool Disable();

	Entity* GetEntity();
	void SetEntity(Entity* entity);

public:
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update() { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };

protected:
	virtual void OnCreate() {};
	virtual void OnDestroy() {};
	
private:
	bool enabled;
	Entity* entity;
};
#endif //__COMPONENT_H__
