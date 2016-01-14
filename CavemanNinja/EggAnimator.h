#ifndef __EGGANIMATOR_H__
#define __EGGANIMATOR_H__

#include "Animator.h"

class EggAnimator : public Animator
{
private:
	EggAnimator(AnimationState* initialState);

public:
	static EggAnimator* Create();
};
#endif	// __EGGANIMATOR_H__