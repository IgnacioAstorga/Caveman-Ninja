#ifndef __ROLLINGBALLANANIMATOR_H__
#define __ROLLINGBALLANANIMATOR_H__

#include "Animator.h"

class RollingBallAnimator : public Animator
{
private:
	RollingBallAnimator(AnimationState* initialState);

public:
	static RollingBallAnimator* Create();
};
#endif	// __ROLLINGBALLANANIMATOR_H__