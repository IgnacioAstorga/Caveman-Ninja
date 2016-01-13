#ifndef __ENEMYTHROWERANIMATOR_H__
#define __ENEMYTHROWERANIMATOR_H__

#include "Animator.h"

class EnemyThrowerAnimator : public Animator
{
private:
	EnemyThrowerAnimator(AnimationState* initialState);

public:
	static EnemyThrowerAnimator* Create();
};
#endif	// __ENEMYTHROWERANIMATOR_H__