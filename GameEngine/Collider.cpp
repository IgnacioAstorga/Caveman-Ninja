#include "Collider.h"
#include "CollisionListener.h"
#include "Transform.h"

#include <algorithm>

Collider::Collider(CollisionListener* listener, Transform* transform, int type, bool enabled) : enabled(enabled)
{
	this->listener = listener;
	this->transform = transform;
	this->type = type;
}

Collider::~Collider()
{
	// En principio no hace nada
}

bool Collider::IsEnabled()
{
	return enabled;
}

bool Collider::Enable()
{
	if (enabled == true)
		return false;

	enabled = true;
	return true;
}

bool Collider::Disable()
{
	if (enabled == false)
		return false;

	enabled = false;
	return true;
}

bool Collider::Start()
{
	// Crea las lista de colisiones
	thisFrameCollisions = new list<Collider*>();
	lastFrameCollisions = new list<Collider*>();

	return OnStartCollider();
}

bool Collider::CleanUp()
{
	// Borra las listas de colisiones
	RELEASE(thisFrameCollisions);
	RELEASE(lastFrameCollisions);

	return OnCleanUpCollider();
}

bool Collider::CollidesWith(Collider* other)
{
	// Pide al otro collider que le llame para aprovecharse del polimorfismo
	return other->CallMe(this);
}

void Collider::NotifyCollision(Collider* other)
{
	if (find(lastFrameCollisions->begin(), lastFrameCollisions->end(), other) != lastFrameCollisions->end())
		listener->OnCollisionStay(this, other);
	else
		listener->OnCollisionEnter(this, other);
	thisFrameCollisions->push_back(other);
}

void Collider::CheckExitCollisions()
{
	// Comprueba con qué colliders ya no se está colisionando
	for (list<Collider*>::iterator it = lastFrameCollisions->begin(); it != lastFrameCollisions->end(); ++it)
		if (find(thisFrameCollisions->begin(), thisFrameCollisions->end(), *it) == thisFrameCollisions->end())
			listener->OnCollisionExit(this, *it);
}

void Collider::ClearFrameCollisions()
{
	// Intercambia las listas de colisiones
	list<Collider*>* temp = lastFrameCollisions;
	lastFrameCollisions = thisFrameCollisions;
	thisFrameCollisions = temp;

	// Vacía la lista de colisiones actuales
	thisFrameCollisions->clear();
}

int Collider::GetType()
{
	return type;
}
