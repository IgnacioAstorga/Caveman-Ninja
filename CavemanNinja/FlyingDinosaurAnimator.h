#ifndef __FLYINGDINOSAURANIMATOR_H__
#define __FLYINGDINOSAURANIMATOR_H__

#include "Animator.h"

class FlyingDinosaurAnimator : public Animator
{
private:
	FlyingDinosaurAnimator(AnimationState* initialState);

public:
	static FlyingDinosaurAnimator* Create();
};
#endif	// __FLYINGDINOSAURANIMATOR_H__