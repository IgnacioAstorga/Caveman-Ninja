#ifndef __FLAGEQUALSCONDITION_H__
#define __FLAGEQUALSCONDITION_H__

#include "FlagCondition.h"

using namespace std;

class FlagEqualsCondition : public FlagCondition
{
public:
	FlagEqualsCondition(string flag, float value)
	{
		this->flag = flag;
		this->value = value;
	}

	~FlagEqualsCondition()
	{
		// No hace nada
	}

	bool IsTrue(unordered_map<string, float>& flags)
	{
		if (flags.find(flag) == flags.end())
			return false;
		return flags[flag] == value;
	}

private:
	string flag;
	float value;
};
#endif // __FLAGEQUALSCONDITION_H__
