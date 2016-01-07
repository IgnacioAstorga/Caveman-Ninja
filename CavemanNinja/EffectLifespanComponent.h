#ifndef __EFFECTLIFESPANCOMPONENT_H__
#define __EFFECTLIFESPANCOMPONENT_H__

#include "Component.h"

class EffectLifespanComponent : public Component
{
public:
	EffectLifespanComponent(float lifeTime);
	virtual ~EffectLifespanComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	void Reset();
	void Reset(float lifeTime);

public:
	float lifeTime;
	float duration;
};
#endif // __EFFECTLIFESPANCOMPONENT_H__