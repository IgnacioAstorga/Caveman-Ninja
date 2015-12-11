#include "Transform.h"

Transform::Transform(Entity* parent)
{
	this->parent = parent;
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
	if (parent == nullptr)
		return GetLocalPosition();
	else
		return parent->transform->GetGlobalPosition();
}

fPoint Transform::GetLocalSpeed()
{
	return speed;
}

fPoint Transform::GetGlobalSpeed()
{
	if (parent == nullptr)
		return GetLocalSpeed();
	else
		return parent->transform->GetGlobalSpeed();
}

float Transform::GetLocalRotation()
{
	return rotation;
}

float Transform::GetGlobalRotation()
{
	if (parent == nullptr)
		return GetLocalRotation();
	else
		return parent->transform->GetGlobalRotation();
}

fPoint Transform::GetLocalScale()
{
	return scale;
}

fPoint Transform::GetGlobalScale()
{
	if (parent == nullptr)
		return GetLocalScale();
	else
		return parent->transform->GetGlobalScale();
}

fPoint Transform::GetForwardVector()
{
	return fPoint(cos(rotation), sin(rotation));
}

fPoint Transform::GetBackwardVector()
{
	return GetForwardVector().Negate();
}

fPoint Transform::GetRightVector()
{
	return fPoint(sin(rotation), -cos(rotation));
}

fPoint Transform::GetLeftVector()
{
	return GetRightVector().Negate();
}