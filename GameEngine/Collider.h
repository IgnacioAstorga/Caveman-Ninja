#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Point.h"

#include <list>
#include <vector>

class CollisionListener;
class Transform;
struct SDL_Rect;

class CircleCollider;
class CircleTraceCollider;
class RectangleCollider;
class RectangleBasicCollider;
class LineCollider;

using namespace std;

class Collider
{
public:
	Collider(CollisionListener* listener, Transform* transform, int type = -1, bool enabled = true);
	Collider(CollisionListener* listener, Transform* transform, vector<int> collisionsTypes, int type = -1, bool enabled = true);
	virtual ~Collider();

public:
	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	bool Start();
	bool CleanUp();

	void PreUpdate();
	void Update();
	void PostUpdate();

protected:
	virtual bool OnStartCollider() { return true; };
	virtual bool OnCleanUpCollider() { return true; }

	virtual void OnPreUpdate() {};
	virtual void OnUpdate() {};
	virtual void OnPostUpdate() {};

public:
	bool CanCollideWithType(int type) const;
	bool CollidesWith(const Collider* other) const;
	void NotifyCollision(Collider* other);
	void CheckExitCollisions();
	void ClearFrameCollisions();
	int GetType() const;

public:
	virtual bool CallMe(const Collider* self) const = 0;

	virtual bool CheckCollision(const CircleCollider* other) const = 0;
	virtual bool CheckCollision(const CircleTraceCollider* other) const = 0;
	virtual bool CheckCollision(const RectangleCollider* other) const = 0;
	virtual bool CheckCollision(const RectangleBasicCollider* other) const = 0;
	virtual bool CheckCollision(const LineCollider* other) const = 0;

	virtual void DrawCollider() const = 0;

	virtual fPoint GetCenter() const = 0;
	virtual fPoint GetExternalPositionFromCoordinates(fPoint coordinates) const = 0;

public:
	bool enabled;
	CollisionListener* listener;
	Transform* transform;
	int type;

	list<Collider*>* lastFrameCollisions;
	list<Collider*>* thisFrameCollisions;

	bool hasSpecificCollisionsTypes;
	vector<int> collisionsTypes;

	bool started;
};
#endif // __COLLIDER_H__