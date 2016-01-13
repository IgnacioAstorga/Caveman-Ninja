#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Point.h"

class Entity;

class Transform
{
public:
	Transform(Entity* entity);
	virtual ~Transform();

	void SetPosition(float xPosition, float yPosition);
	void SetGlobalPosition(float xPosition, float yPosition);
	void SetSpeed(float xSpeed, float ySpeed);
	void SetGlobalSpeed(float xSpeed, float ySpeed);
	void SetRotation(float rotation);
	void SetGlobalRotation(float rotation);
	void SetScale(float scale);
	void SetScale(float xScale, float yScale);
	void SetGlobalScale(float scale);
	void SetGlobalScale(float xScale, float yScale);

	fPoint GetLocalPosition() const;
	fPoint GetGlobalPosition() const;
	fPoint GetLocalSpeed() const;
	fPoint GetGlobalSpeed() const;
	float GetLocalRotation() const;
	float GetGlobalRotation() const;
	fPoint GetLocalScale() const;
	fPoint GetGlobalScale() const;

	fPoint GetForwardVector() const;
	fPoint GetBackwardVector() const;
	fPoint GetRightVector() const;
	fPoint GetLeftVector() const;

	void Move(float x, float y);
	void Move(fPoint distance);
	void Rotate(float angle);
	void Accelerate(float x, float y);
	void Accelerate(fPoint acceleration);
	void Resize(float scale);
	void Resize(float x, float y);
	void Resize(fPoint scale);

public:
	fPoint position;
	fPoint speed;
	float rotation;
	fPoint scale;

private:
	Entity* entity;
};
#endif //__TRANSFORM_H__
