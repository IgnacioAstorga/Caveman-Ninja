#ifndef __FLAGGREATERTHANCONDITION_H__
#define __FLAGGREATERTHANCONDITION_H__

#include "FlagCondition.h"

using namespace std;

class FlagGreaterThanCondition : public FlagCondition
{
public:
	FlagGreaterThanCondition(string flag, float value)
	{
		this->flag = flag;
		this->value = value;
	}

	~FlagGreaterThanCondition()
	{
		// No hace nada
	}

	bool IsTrue(const unordered_map<string, float>& flags) const
	{
		if (flags.find(flag) == flags.end())
			return false;
		return flags.at(flag) > value;
	}

private:
	string flag;
	float value;
};
#endif // __FLAGGREATERTHANCONDITION_H__
