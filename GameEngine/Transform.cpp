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
	// Se transforma una posici�n global en local
	this->position = fPoint(xPosition, yPosition) - entity->GetParent()->transform->GetGlobalPosition();
}

void Transform::SetSpeed(float xSpeed, float ySpeed)
{
	speed = fPoint(xSpeed, ySpeed);
}

void Transform::SetGlobalSpeed(float xSpeed, float ySpeed)
{
	if (entity->GetParent() == nullptr)
		return SetSpeed(xSpeed, ySpeed);
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
	// Se transforma una rotaci�n global en local
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

fPoint Transform::GetLocalPosition() const
{
	return position;
}

fPoint Transform::GetGlobalPosition() const
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

fPoint Transform::GetLocalSpeed() const
{
	return speed;
}

fPoint Transform::GetGlobalSpeed() const
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

float Transform::GetLocalRotation() const
{
	return rotation;
}

float Transform::GetGlobalRotation() const
{
	if (entity->GetParent() == nullptr)
		return GetLocalRotation();
	else
		return entity->GetParent()->transform->GetGlobalRotation() + GetLocalRotation();
}

fPoint Transform::GetLocalScale() const
{
	return scale;
}

fPoint Transform::GetGlobalScale() const
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

fPoint Transform::GetForwardVector() const
{
	double rads = rotation * 2 * M_PI / 360.0;
	return fPoint((float)cos(rads), (float)sin(rads));
}

fPoint Transform::GetBackwardVector() const
{
	return GetForwardVector().Negate();
}

fPoint Transform::GetRightVector() const
{
	double rads = rotation * 2 * M_PI / 360.0;
	return fPoint((float)sin(rads), (float)-cos(rads));
}

fPoint Transform::GetLeftVector() const
{
	return GetRightVector().Negate();
}

void Transform::Move(float x, float y)
{
	position.x += x;
	position.y += y;
}

void Transform::Move(fPoint distance)
{
	Move(distance.x, distance.y);
}

void Transform::Rotate(float angle)
{
	rotation += angle;
}

void Transform::Accelerate(float x, float y)
{
	speed.x += x;
	speed.y += y;
}

void Transform::Accelerate(fPoint acceleration)
{
	Accelerate(acceleration.x, acceleration.y);
}

void Transform::Resize(float scale)
{
	Resize(scale, scale);
}

void Transform::Resize(float x, float y)
{
	scale.x *= x;
	scale.y *= y;
}

void Transform::Resize(fPoint scale)
{
	Resize(scale.x, scale.y);
}
