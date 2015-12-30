#include "Transform.h"
#include "Entity.h"

Transform::Transform(Entity* entity)
{
	this->entity = entity;
	position = fPoint(0.0f, 0.0f);
	speed = fPoint(0.0f, 0.0f);
	rotation = 0.0f;
	scale = fPoint(1.0f, 1.0f);
}

Transform::~Transform()
{
	// En principio no hace nada
}

void Transform::SetPosition(float xPosition, float yPosition)
{
	position = fPoint(xPosition, yPosition);
}

void Transform::SetGlobalPosition(float xPosition, float yPosition)
{
	if (entity->GetParent() == nullptr)
		return SetPosition(xPosition, yPosition);
	// Se transforma una posición global en local
	this->position = fPoint(xPosition, yPosition) - entity->GetParent()->transform->GetGlobalPosition();
}

void Transform::SetSpeed(float xSpeed, float ySpeed)
{
	speed = fPoint(xSpeed, ySpeed);
}

void Transform::SetGlobalSpeed(float xSpeed, float ySpeed)
{
	if (entity->GetParent() == nullptr)
		return SetSpeed(xSpeed, xSpeed);
	// Se transforma una velocidad global en local
	this->speed = fPoint(xSpeed, ySpeed) - entity->GetParent()->transform->GetGlobalSpeed();
}

void Transform::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Transform::SetGlobalRotation(float rotation)
{
	if (entity->GetParent() == nullptr)
		return SetRotation(rotation);
	// Se transforma una rotación global en local
	this->rotation = rotation - entity->GetParent()->transform->GetGlobalRotation();
}

void Transform::SetScale(float scale)
{
	SetScale(scale, scale);
}

void Transform::SetScale(float xScale, float yScale)
{
	scale = fPoint(xScale, yScale);
}

void Transform::SetGlobalScale(float scale)
{
	SetGlobalScale(scale, scale);
}

void Transform::SetGlobalScale(float xScale, float yScale)
{
	if (entity->GetParent() == nullptr)
		return SetScale(xScale, yScale);
	// Se transforma una velocidad global en local
	this->scale = fPoint(xScale, yScale) - entity->GetParent()->transform->GetGlobalScale();
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