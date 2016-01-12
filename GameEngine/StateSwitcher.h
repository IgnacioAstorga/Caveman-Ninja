#ifndef __STATESWITCHER_H__
#define __STATESWITCHER_H__

#include "Globals.h"

#include <list>
#include <unordered_map>

template <class T>
class StateTransition;

using namespace std;

template <class T>
class StateSwitcher
{
public:
	StateSwitcher(T* state);
	virtual ~StateSwitcher();

	void AddStateTransition(StateTransition<T>* stateTransition);
	list<StateSwitcher<T>*> GetReachableStateSwitchers() const;

	T* GetActualState() const;
	StateSwitcher<T>* Process(unordered_map<string, float>& flags);

protected:
	T* state;
	list<StateTransition<T>*> stateTransitions;
};

#include "StateTransition.h"

template<class T>
StateSwitcher<T>::StateSwitcher(T* state)
{
	this->state = state;
}

template<class T>
StateSwitcher<T>::~StateSwitcher()
{
	for (list<StateTransition<T>*>::iterator it = stateTransitions.begin(); it != stateTransitions.end(); ++it)
		RELEASE(*it);
	stateTransitions.clear();
	RELEASE(state);
}

template<class T>
void StateSwitcher<T>::AddStateTransition(StateTransition<T>* stateTransition)
{
	if (find(stateTransitions.begin(), stateTransitions.end(), stateTransition) == stateTransitions.end())
		stateTransitions.push_back(stateTransition);
}

template<class T>
list<StateSwitcher<T>*> StateSwitcher<T>::GetReachableStateSwitchers() const
{
	list<StateSwitcher<T>*> reachableStateSwitchers;
	for (list<StateTransition<T>*>::const_iterator it = stateTransitions.begin(); it != stateTransitions.end(); ++it)
		reachableStateSwitchers.push_back((*it)->GetTargetStateSwitcher());
	return reachableStateSwitchers;
}

template<class T>
T* StateSwitcher<T>::GetActualState() const
{
	return state;
}

template<class T>
StateSwitcher<T>* StateSwitcher<T>::Process(unordered_map<string, float>& flags)
{
	StateSwitcher<T>* newStateSwitcher = nullptr;
	for (list<StateTransition<T>*>::iterator it = stateTransitions.begin(); it != stateTransitions.end() && newStateSwitcher == nullptr; ++it)
		newStateSwitcher = (*it)->Process(flags);

	if (newStateSwitcher != nullptr)
		return newStateSwitcher;
	else
		return this;
}
#endif // __STATESWITCHER_H__