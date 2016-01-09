#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(bool start_enabled)
	: Component(start_enabled)
{
	this->hasSpecificCollisionsTypes = false;
}

ColliderComponent::ColliderComponent(vector<int> collisionsTypes, bool start_enabled)
{
	this->hasSpecificCollisionsTypes = true;
	this->collisionsTypes = collisionsTypes;
}

ColliderComponent::~ColliderComponent()
{
	// No hace nada
}
