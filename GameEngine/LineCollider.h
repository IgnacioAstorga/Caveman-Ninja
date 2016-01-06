#ifndef __LINECOLLIDER_H__
#define __LINECOLLIDER_H__

#include "Collider.h"
#include "Point.h"

#include <vector>

using namespace std;

class LineCollider : public Collider
{
public:
	LineCollider(CollisionListener* listener, Transform* transform, vector<fPoint> points, float thickness, int type = -1, bool start_enabled = true);
	~LineCollider();

	bool CallMe(Collider* self);
	bool CheckCollision(CircleCollider* other);
	bool CheckCollision(CircleTraceCollider* other);
	bool CheckCollision(RectangleCollider* other);
	bool CheckCollision(LineCollider* other);
	void DrawCollider();

public:
	fPoint GetPointGlobalCoordinates(unsigned int index);
	RectangleCollider CreateSegmentCollider(int leftBoundIndex);
	fPoint GetCenter();

public:
	float thickness;
	vector<fPoint> points;
};

#endif // __LINECOLLIDER_H__