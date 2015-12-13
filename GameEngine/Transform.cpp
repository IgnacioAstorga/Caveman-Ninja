#include "Transform.h"
#include "Entity.h"

Transform::Transform(Entity* entity)
{
	this->entity = entity;
	scale = fPoint(1.0f, 1.0f);
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
	{
		fPoint temp = GetLocalPosition().Rotate(entity->GetParent()->transform->GetLocalRotation());
		temp.x *= entity->GetParent()->transform->GetGlobalScale().x;
		temp.y *= entity->GetParent()->transform->GetGlobalScale().y;
		return  entity->GetParent()->transform->GetGlobalPosition() + temp;
	}
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
	{
		fPoint temp = GetLocalSpeed().Rotate(entity->GetParent()->transform->GetLocalRotation());
		temp.x *= entity->GetParent()->transform->GetGlobalScale().x;
		temp.y *= entity->GetParent()->transform->GetGlobalScale().y;
		return  entity->GetParent()->transform->GetGlobalSpeed() + temp;
	}
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
	{
		fPoint temp = GetLocalScale();
		temp.x *= entity->GetParent()->transform->GetGlobalScale().x;
		temp.y *= entity->GetParent()->transform->GetGlobalScale().y;
		return  temp;
	}
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