#pragma once
#include <vector>

#include "SortDefinitions.h"
#include "State.h"

class StateManager
{
public:
	void addState(const State &);
	void clearStates();

	State getCurrentState() const;
	State getNextState();
	State getPreviousState();
	State getFirstState();
	State getLastState();
	bool hasStates() const;

	StateContext getStateContext() const;
	void setContextCurrentState(const StateContext & context);

	SortType getSortType() const;
	void setSortType(SortType);

private:
	std::vector<State> states;
	SortType sortType{SortType::BubbleSort};
	int currentStateIndex{0};
};
