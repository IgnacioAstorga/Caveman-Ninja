#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "Module.h"

#include <list>

class Collider;

using namespace std;

class ModuleCollisions : public Module
{
public:
	ModuleCollisions(bool start_enabled = true);
	~ModuleCollisions();

public:
	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	void RegisterCollider(Collider* collider);
	void UnregisterCollider(Collider* collider);

private:
	list<Collider*> colliders;
};
#endif // __MODULECOLLISIONS_H__
