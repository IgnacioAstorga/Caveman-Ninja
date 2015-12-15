#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "CollisionListener.h"
#include "Globals.h"

class Entity;

class Component : public CollisionListener
{
public:
	Component(bool start_enabled = true);
	virtual ~Component();

public:
	bool IsEnabled();
	bool Enable();
	bool Disable();

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
	virtual bool OnPreUpdate() { return true; };
	virtual bool OnUpdate() { return true; };
	virtual bool OnPostUpdate() { return true; };
	virtual bool OnCleanUp() { return true; };

public:
	virtual bool OnCollisionEnter(Collider* self, Collider* other) { return true; };
	virtual bool OnCollisionStay(Collider* self, Collider* other) { return true; };
	virtual bool OnCollisionExit(Collider* self, Collider* other) { return true; };

public:
	Entity* entity;
	
private:
	bool enabled;
	bool started;
};
#endif //__COMPONENT_H__
