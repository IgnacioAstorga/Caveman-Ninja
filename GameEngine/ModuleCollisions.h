#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "Module.h"
#include "Point.h"

#include <list>

class Collider;
struct SDL_Texture;

using namespace std;

class ModuleCollisions : public Module
{
public:
	ModuleCollisions(bool start_enabled = true);
	~ModuleCollisions();

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	void RegisterCollider(Collider* collider);
	void UnregisterCollider(Collider* collider);
	list<Collider*> CheckCollisions(Collider* collider);

private:
	list<Collider*> colliders;

public:
	SDL_Texture* circle;
	SDL_Texture* square;
};
#endif // __MODULECOLLISIONS_H__
