#ifndef __COLLISIONLISTENER_H__
#define __COLLISIONLISTENER_H__

class Collider;

class CollisionListener
{
public:
	virtual bool OnCollisionEnter(Collider* self, Collider* other) = 0;
	virtual bool OnCollisionStay(Collider* self, Collider* other) = 0;
	virtual bool OnCollisionExit(Collider* self, Collider* other) = 0;
};
#endif // __COLLISIONLISTENER_H__
