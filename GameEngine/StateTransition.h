#ifndef __STATESTRANSITION_H__
#define __STATESTRANSITION_H__

#include "Globals.h"
#include "FlagCondition.h"

#include <string>
#include <unordered_map>

using namespace std;

template <class T>
class StateTransition
{
public:
	StateTransition(StateSwitcher<T>* targetStateSwitcher, FlagCondition* flagCondition);
	virtual ~StateTransition();

	StateSwitcher<T>* GetTargetStateSwitcher() const;

	StateSwitcher<T>* Process(unordered_map<string, float>& flags);

protected:
	FlagCondition* flagCondition;
	StateSwitcher<T>* targetStateSwitcher;
};

template<class T>
StateTransition<T>::StateTransition(StateSwitcher<T>* targetStateSwitcher, FlagCondition* flagCondition)
{
	this->targetStateSwitcher = targetStateSwitcher;
	this->flagCondition = flagCondition;
}

template<class T>
StateTransition<T>::~StateTransition()
{
	RELEASE(flagCondition);
}

template<class T>
StateSwitcher<T>* StateTransition<T>::GetTargetStateSwitcher() const
{
	return targetStateSwitcher;
}

template<class T>
StateSwitcher<T>* StateTransition<T>::Process(unordered_map<string, float>& flags)
{
	if (flagCondition->IsTrue(flags))
		return targetStateSwitcher;
	return nullptr;
}
#endif // __STATESTRANSITION_H__