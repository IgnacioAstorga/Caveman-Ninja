#ifndef __PLAYERANIMATOR_H__
#define __PLAYERANIMATOR_H__

#include "Animator.h"

class PlayerAnimator : public Animator
{
public:
	PlayerAnimator(StateSwitcher<Animation>* initialState);
	static PlayerAnimator* Create();
};
#endif	// __PLAYERANIMATOR_H__