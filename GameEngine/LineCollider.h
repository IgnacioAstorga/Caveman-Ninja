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
	LineCollider(CollisionListener* listener, Transform* transform, vector<fPoint> points, float thickness, vector<int> collisionsTypes, int type = -1, bool start_enabled = true);
	~LineCollider();

	bool CallMe(const Collider* self) const;
	bool CheckCollision(const CircleCollider* other) const;
	bool CheckCollision(const CircleTraceCollider* other) const;
	bool CheckCollision(const RectangleCollider* other) const;
	bool CheckCollision(const RectangleBasicCollider* other) const;
	bool CheckCollision(const LineCollider* other) const;
	void DrawCollider() const;

public:
	fPoint GetExternalPositionFromCoordinates(fPoint coordinates) const;
	fPoint GetPointGlobalCoordinates(unsigned int index) const;
	RectangleCollider CreateSegmentCollider(int leftBoundIndex) const;
	fPoint GetCenter() const;

public:
	float thickness;
	vector<fPoint> points;
};

#endif // __LINECOLLIDER_H__