#ifndef __TOMAHAWKANIMATOR_H__
#define __TOMAHAWKANIMATOR_H__

#include "Animator.h"

class TomahawkAnimator : public Animator
{
public:
	TomahawkAnimator(AnimationState* initialState);
	static TomahawkAnimator* Create();
};
#endif	// __TOMAHAWKANIMATOR_H__