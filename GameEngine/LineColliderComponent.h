#ifndef __LINECOLLIDERCOMPONENT_H__
#define __LINECOLLIDERCOMPONENT_H__

#include "ColliderComponent.h"
#include "Point.h"

class LineCollider;

class LineColliderComponent : public ColliderComponent
{
public:
	LineColliderComponent(vector<fPoint> points, float thickness, int type = -1, bool start_enabled = true);
	LineColliderComponent(vector<fPoint> points, float thickness, vector<int> collisionsTypes, int type = -1, bool start_enabled = true);
	virtual ~LineColliderComponent();

	bool OnStart();
	bool OnCleanUp();

public:
	void SetThickness(float thickness);
	void AddPoint(fPoint point);
	void AddPoint(fPoint point, int index);
	void SetPoint(fPoint point, int index);
	void RemovePoint(int index);
	Collider* GetCollider();

private:
	vector<fPoint> points;
	float thickness;
	int type;

	LineCollider* collider;
};

#endif // __LINECOLLIDERCOMPONENT_H__