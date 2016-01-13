#ifndef __AIBEHAVIOUR_H__
#define __AIBEHAVIOUR_H__

class AIManager;
class Entity;

class AIBehaviour
{
public:
	AIBehaviour(int identifier);
	virtual ~AIBehaviour();

public:
	void Configure(AIManager* manager, Entity* entity);
	int GetIdentifier() const;

public:
	virtual void OnEnter() {}
	virtual void OnTick() {}
	virtual void OnExit() {}

protected:
	int identifier;
	AIManager* manager;
	Entity* entity;
};

#endif // __AIBEHAVIOUR_H__