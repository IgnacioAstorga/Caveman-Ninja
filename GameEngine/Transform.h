#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Entity.h"
#include "Point.h"

class Transform
{
public:
	Transform(Entity* parent);
	virtual ~Transform();

	fPoint GetLocalPosition();
	fPoint GetGlobalPosition();
	fPoint GetLocalSpeed();
	fPoint GetGlobalSpeed();
	float GetLocalRotation();
	float GetGlobalRotation();
	fPoint GetLocalScale();
	fPoint GetGlobalScale();

	fPoint GetForwardVector();
	fPoint GetBackwardVector();
	fPoint GetRightVector();
	fPoint GetLeftVector();

public:
	fPoint position;
	fPoint speed;
	float rotation;
	fPoint scale;

private:
	Entity* parent;
};
#endif //__TRANSFORM_H__
