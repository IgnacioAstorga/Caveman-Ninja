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

	bool IsTrue(const unordered_map<string, float>& flags) const
	{
		if (flags.find(ANIMATION_END) == flags.end())
			return false;
		return flags.at(ANIMATION_END) == (float)true;
	}
};
#endif // __ANIMATIONENDCONDITION_H__
