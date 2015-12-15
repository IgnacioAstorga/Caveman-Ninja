#ifndef __FLAGLESSTHANCONDITION_H__
#define __FLAGLESSTHANCONDITION_H__

#include "FlagCondition.h"

using namespace std;

class FlagLessThanCondition : public FlagCondition
{
public:
	FlagLessThanCondition(string flag, float value)
	{
		this->flag = flag;
		this->value = value;
	}

	~FlagLessThanCondition()
	{
		// No hace nada
	}

	bool IsTrue(unordered_map<string, float>& flags)
	{
		if (flags.find(flag) == flags.end())
			return false;
		return flags[flag] < value;
	}

private:
	string flag;
	float value;
};
#endif // __FLAGLESSTHANCONDITION_H__
