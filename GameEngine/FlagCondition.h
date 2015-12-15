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

	virtual bool IsTrue(unordered_map<string, float>& flags) { return false; };
	virtual bool IsTriggered(unordered_map<string, float>& flags, string trigger) { return false; };
};
#endif // __FLAGCONDITION_H__
