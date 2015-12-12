#include "Transform.h"
#include "Entity.h"

Transform::Transform(Entity* entity)
{
	this->entity = entity;
}

Transform::~Transform()
{
	// En principio no hace nada
}

fPoint Transform::GetLocalPosition()
{
	return position;
}

fPoint Transform::GetGlobalPosition()
{
	if (entity->GetParent() == nullptr)
		return GetLocalPosition();
	else
		return entity->GetParent()->transform->GetGlobalPosition() + GetLocalPosition().Rotate(entity->GetParent()->transform->GetLocalRotation());
}

fPoint Transform::GetLocalSpeed()
{
	return speed;
}

fPoint Transform::GetGlobalSpeed()
{
	if (entity->GetParent() == nullptr)
		return GetLocalSpeed();
	else
		return entity->GetParent()->transform->GetGlobalSpeed() + GetLocalSpeed().Rotate(entity->GetParent()->transform->GetLocalRotation());
}

float Transform::GetLocalRotation()
{
	return rotation;
}

float Transform::GetGlobalRotation()
{
	if (entity->GetParent() == nullptr)
		return GetLocalRotation();
	else
		return entity->GetParent()->transform->GetGlobalRotation() + GetLocalRotation();
}

fPoint Transform::GetLocalScale()
{
	return scale;
}

fPoint Transform::GetGlobalScale()
{
	if (entity->GetParent() == nullptr)
		return GetLocalScale();
	else
		return entity->GetParent()->transform->GetGlobalScale() + GetLocalScale();
}

fPoint Transform::GetForwardVector()
{
	double rads = rotation * 2 * M_PI / 360.0;
	return fPoint((float)cos(rads), (float)sin(rads));
}

fPoint Transform::GetBackwardVector()
{
	return GetForwardVector().Negate();
}

fPoint Transform::GetRightVector()
{
	double rads = rotation * 2 * M_PI / 360.0;
	return fPoint((float)sin(rads), (float)-cos(rads));
}

fPoint Transform::GetLeftVector()
{
	return GetRightVector().Negate();
}