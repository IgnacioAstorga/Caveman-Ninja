#include "ModuleCollisions.h"
#include "Collider.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleTextures.h"

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

	// Carga las texturas de los colliders
	circle = App->textures->Load("circle_64.png");
	square = App->textures->Load("square_64.png");

	return true;
}

update_status ModuleCollisions::PreUpdate()
{
	// Hace preupdate a los colliders que tengan que realizar alguna operación previa
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->PreUpdate();

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	// Hace update a los colliders que tengan que realizar alguna operación
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->Update();

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
	// Hace postupdate a los colliders que tengan que realizar alguna operación posterior
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->PostUpdate();

	// Hace PostUpdate a los colliders para que registren el fin de la frame actual y borren las colisiones registradas
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->ClearFrameCollisions();

	// Si está en modo DEBUG, pinta los colliders
	if (DEBUG == true)
		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->DrawCollider();

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

	// Descarga las texturas de los colliders
	App->textures->Unload(circle);
	App->textures->Unload(square);

	return true;
}

void ModuleCollisions::RegisterCollider(Collider* collider)
{
	LOG("Collider registration");

	if (std::find(colliders.begin(), colliders.end(), collider) == colliders.end())
		colliders.push_back(collider);
}

void ModuleCollisions::UnregisterCollider(Collider* collider)
{
	LOG("Collider unregistration");

	if (std::find(colliders.begin(), colliders.end(), collider) != colliders.end())
		colliders.remove(collider);
}

list<Collider*> ModuleCollisions::CheckCollisions(Collider* collider)
{
	// Devuelve los colliders que colisionan con el collider especificado (ignora al propio collider)
	list<Collider*> ret;
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		if ((*it)->IsEnabled() && *it != collider && collider->CollidesWith(*it))
			ret.push_back(*it);
	return ret;
}
