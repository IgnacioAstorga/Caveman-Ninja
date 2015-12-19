#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "StateSwitcher.h"
#include "Globals.h"

#include <list>
#include <unordered_map>
#include <string>

using namespace std;

template <class T>
class StateMachine
{
public:
	StateMachine(StateSwitcher<T>* startingStateSwitcher);
	virtual ~StateMachine();

	void RegisterStateSwitcher(StateSwitcher<T>* stateSwitcher);

	T* GetActualState();
	StateSwitcher<T>* SetFlagValue(string flag, bool value);
	StateSwitcher<T>* SetFlagValue(string flag, int value);
	StateSwitcher<T>* SetFlagValue(string flag, float value);
	StateSwitcher<T>* TriggerFlag(string flag);

protected:
	virtual void OnStateTransition(T* lastState, T* newState) {};

protected:
	StateSwitcher<T>* currentStateSwitcher;
	list<StateSwitcher<T>*> stateSwitchers;
	unordered_map<string, float> flags;
};

template<class T>
StateMachine<T>::StateMachine(StateSwitcher<T>* startingStateSwitcher)
{
	this->currentStateSwitcher = startingStateSwitcher;
	RegisterStateSwitcher(currentStateSwitcher);
}

template<class T>
StateMachine<T>::~StateMachine()
{
	for (list<StateSwitcher<T>*>::iterator it = stateSwitchers.begin(); it != stateSwitchers.end(); ++it)
		RELEASE(*it);
	stateSwitchers.clear();
}

template<class T>
void StateMachine<T>::RegisterStateSwitcher(StateSwitcher<T>* stateSwitcher)
{
	if (find(stateSwitchers.begin(), stateSwitchers.end(), stateSwitcher) == stateSwitchers.end())
	{
		stateSwitchers.push_back(stateSwitcher);
		list<StateSwitcher<T>*> reachableStateSwitchers = stateSwitcher->GetReachableStateSwitchers();
		for (list<StateSwitcher<T>*>::iterator it = reachableStateSwitchers.begin(); it != reachableStateSwitchers.end(); ++it)
			RegisterStateSwitcher(*it);
	}
}

template<class T>
T* StateMachine<T>::GetActualState()
{
	return currentStateSwitcher->GetActualState();
}

template<class T>
StateSwitcher<T>* StateMachine<T>::SetFlagValue(string flag, bool value)
{
	flags[flag] = value;
	StateMachine<T>* newStateSwitcher = currentStateSwitcher->Process(&flags);
	if (newStateSwitcher != currentStateSwitcher)
	{
		OnStateTransition(currentStateSwitcher->GetActualState(), newStateSwitcher->GetActualState());
		currentStateSwitcher = newStateSwitcher;
	}
	return currentStateSwitcher;
}

template<class T>
StateSwitcher<T>* StateMachine<T>::SetFlagValue(string flag, int value)
{
	flags[flag] = value;
	StateSwitcher<T>* newStateSwitcher = currentStateSwitcher->Process(flags);
	if (newStateSwitcher != currentStateSwitcher)
	{
		OnStateTransition(currentStateSwitcher->GetActualState(), newStateSwitcher->GetActualState());
		currentStateSwitcher = newStateSwitcher;
	}
	return currentStateSwitcher
}

template<class T>
StateSwitcher<T>* StateMachine<T>::SetFlagValue(string flag, float value)
{
	flags[flag] = value;
	StateSwitcher<T>* newStateSwitcher = currentStateSwitcher->Process(flags);
	if (newStateSwitcher != currentStateSwitcher)
	{
		OnStateTransition(currentStateSwitcher->GetActualState(), newStateSwitcher->GetActualState());
		currentStateSwitcher = newStateSwitcher;
	}
	return currentStateSwitcher;
}

template<class T>
StateSwitcher<T>* StateMachine<T>::TriggerFlag(string flag)
{
	StateMachine<T>* newStateSwitcher = currentStateSwitcher->Trigger(flags, flag);
	if (newStateSwitcher != currentStateSwitcher)
	{
		OnStateTransition(currentStateSwitcher->GetActualState(), newStateSwitcher->GetActualState());
		currentStateSwitcher = newStateSwitcher;
	}
	return currentStateSwitcher;
}
#endif // __STATEMACHINE_H__