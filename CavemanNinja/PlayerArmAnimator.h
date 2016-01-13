#ifndef __PLAYERARMANIMATOR_H__
#define __PLAYERARMANIMATOR_H__

#include "Animator.h"

class PlayerArmAnimator : public Animator
{
public:
	PlayerArmAnimator(AnimationState* initialState);
	static PlayerArmAnimator* Create();
};
#endif	// __PLAYERARMANIMATOR_H__