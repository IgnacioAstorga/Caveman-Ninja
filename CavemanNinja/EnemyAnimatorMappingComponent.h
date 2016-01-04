#ifndef __ENEMYANIMATORMAPPINGCOMPONENT_H__
#define __ENEMYANIMATORMAPPINGCOMPONENT_H__

#include "Component.h"

class Animator;
class DieOnPlayerAttackComponent;

class EnemyAnimatorMappingComponent : public Component
{
public:
	EnemyAnimatorMappingComponent();
	virtual ~EnemyAnimatorMappingComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	Animator* animator;
	DieOnPlayerAttackComponent* lifeComponent;
};
#endif // __ENEMYANIMATORMAPPINGCOMPONENT_H__