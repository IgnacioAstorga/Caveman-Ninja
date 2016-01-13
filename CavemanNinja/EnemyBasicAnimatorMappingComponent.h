#ifndef __ENEMYBASICANIMATORMAPPINGCOMPONENT_H__
#define __ENEMYBASICANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class DieOnPlayerAttackComponent;

class EnemyBasicAnimatorMappingComponent : public Component
{
public:
	EnemyBasicAnimatorMappingComponent();
	virtual ~EnemyBasicAnimatorMappingComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	Animator* animator;
	DieOnPlayerAttackComponent* lifeComponent;
};
#endif // __ENEMYBASICANIMATORMAPPINGCOMPONENT_H__