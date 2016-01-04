#ifndef __ENEMYCAVEMANANIMATOR_H__
#define __ENEMYCAVEMANANIMATOR_H__

#include "Animator.h"

class DieOnPlayerAttackComponent;

class EnemyCavemanAnimator : public Animator
{
private:
	EnemyCavemanAnimator(StateSwitcher<Animation>* initialState);

public:
	static EnemyCavemanAnimator* Create();
};
#endif	// __ENEMYCAVEMANANIMATOR_H__