#include "Collider.h"
#include "CollisionListener.h"
#include "Transform.h"

#include <algorithm>

Collider::Collider(CollisionListener* listener, Transform* transform, int type, bool enabled) : enabled(enabled)
{
	this->listener = listener;
	this->transform = transform;
	this->type = type;

	this->started = false;
	this->hasSpecificCollisionsTypes = false;
}

Collider::Collider(CollisionListener* listener, Transform* transform, vector<int> collisionsTypes, int type, bool enabled) : enabled(enabled)
{
	this->listener = listener;
	this->transform = transform;
	this->type = type;

	this->started = false;
	this->hasSpecificCollisionsTypes = true;
	this->collisionsTypes = collisionsTypes;
}

Collider::~Collider()
{
	// En principio no hace nada
}

bool Collider::IsEnabled() const
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
	if (started)
		return true;
	started = true;

	// Crea las lista de colisiones
	thisFrameCollisions = new list<Collider*>();
	lastFrameCollisions = new list<Collider*>();

	return OnStartCollider();
}

bool Collider::CleanUp()
{
	if (!started)
		return true;
	started = false;

	// Borra las listas de colisiones
	RELEASE(thisFrameCollisions);
	RELEASE(lastFrameCollisions);

	return OnCleanUpCollider();
}

void Collider::PreUpdate()
{
	// Llamada al delegado
	OnPreUpdate();
}

void Collider::Update()
{
	// Llamada al delegado
	OnUpdate();
}

void Collider::PostUpdate()
{
	// Llamada al delegado
	OnPostUpdate();
}

bool Collider::CanCollideWithType(int type) const
{
	// Si no tiene tipos específicos, puede colisionar
	if (!hasSpecificCollisionsTypes)
		return true;

	// Comprueba si el tipo es adecuado
	for (unsigned int i = 0; i < collisionsTypes.size(); ++i)
		if (type == collisionsTypes[i])
			return true;

	return false;	// Llegado este punto, no colisiona con el tipo
}

bool Collider::CollidesWith(const Collider* other) const
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

int Collider::GetType() const
{
	return type;
}
