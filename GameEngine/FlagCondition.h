#ifndef __FLAGCONDITION_H__
#define __FLAGCONDITION_H__

#include <string>
#include <unordered_map>

using namespace std;

class FlagCondition
{
public:
	FlagCondition() {};
	virtual ~FlagCondition() {};

	virtual bool IsTrue(const unordered_map<string, float>& flags) const { return false; };
};
#endif // __FLAGCONDITION_H__
