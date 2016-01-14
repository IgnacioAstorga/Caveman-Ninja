#ifndef __SINGLEANIMATION_H__
#define __SINGLEANIMATION_H__

#include "BasicAnimation.h"

class SingleAnimation : public BasicAnimation
{
public:
	SingleAnimation(int width, int height) : BasicAnimation(width, height, 1, 1, 0.0f, false) { frames.push_back({ 0, 0 }); };
	virtual ~SingleAnimation() {};
};
#endif //__SINGLEANIMATION_H__