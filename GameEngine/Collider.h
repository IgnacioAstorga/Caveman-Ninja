#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <list>

class CollisionListener;
class Transform;
struct SDL_Rect;

class CircleCollider;

using namespace std;

class Collider
{
public:
	Collider(CollisionListener* listener, Transform* transform, bool enabled = true);
	virtual ~Collider();

public:
	bool IsEnabled();
	bool Enable();
	bool Disable();

	bool Start();
	bool CleanUp();

protected:
	virtual bool OnStartCollider() { return true; };
	virtual bool OnCleanUpCollider() { return true; }

public:
	bool CollidesWith(Collider* other);
	void NotifyCollision(Collider* other);
	void CheckExitCollisions();
	void ClearFrameCollisions();

public:
	virtual bool CallMe(Collider* self) = 0;
	virtual bool CheckCollision(CircleCollider* other) = 0;

protected:
	bool enabled;
	CollisionListener* listener;
	Transform* transform;
	list<Collider*>* lastFrameCollisions;
	list<Collider*>* thisFrameCollisions;
};
#endif // __COLLIDER_H__