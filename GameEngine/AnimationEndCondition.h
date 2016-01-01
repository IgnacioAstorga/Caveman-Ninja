#ifndef __ANIMATIONENDCONDITION_H__
#define __ANIMATIONENDCONDITION_H__

#include "FlagCondition.h"
#include "Animator.h"

using namespace std;

class AnimationEndCondition : public FlagCondition
{
public:
	AnimationEndCondition() {}

	~AnimationEndCondition() {}

	bool IsTrue(unordered_map<string, float>& flags)
	{
		if (flags.find(ANIMATION_END) == flags.end())
			return false;
		return flags[ANIMATION_END] == (float)true;
	}
};
#endif // __ANIMATIONENDCONDITION_H__
