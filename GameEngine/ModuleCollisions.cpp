#include "ModuleCollisions.h"
#include "Collider.h"

ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled)
{
	// No hace nada
}

ModuleCollisions::~ModuleCollisions()
{
	// No hace nada
}

bool ModuleCollisions::Start()
{
	LOG("Starting up Collisions Module");

	// Arranca la lista de colliders
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->Start();

	return true;
}

update_status ModuleCollisions::Update()
{
	// Para cada collider, comprueba si ha habido collisiones con los demás (lo comprueba sin reflexividad)
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			for (list<Collider*>::iterator other = colliders.begin(); other != colliders.end(); ++other)
				if (*other != *it && (*other)->IsEnabled())
					if ((*it)->CollidesWith(*other))
						(*it)->NotifyCollision(*other);

	// Hace Update a los colliders para que comprueben si alguna colisión ha dejado de producirse
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->CheckExitCollisions();

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	// Hace PostUpdate a los colliders para que registren el fin de la frame actual y borren las colisiones registradas
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->ClearFrameCollisions();

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp()
{
	LOG("Cleaning up Collisions Module");

	// Limpia la lista de colliders
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->CleanUp();
	colliders.clear();

	return true;
}

void ModuleCollisions::RegisterCollider(Collider* collider)
{
	LOG("Animation registration");

	if (std::find(colliders.begin(), colliders.end(), collider) == colliders.end())
		colliders.push_back(collider);
}

void ModuleCollisions::UnregisterCollider(Collider* collider)
{
	LOG("Animation unregistration");

	if (std::find(colliders.begin(), colliders.end(), collider) != colliders.end())
		colliders.remove(collider);
}