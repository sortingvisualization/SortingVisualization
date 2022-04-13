#pragma once
#include <deque>

#include "ArrayModel.h"
#include "SortStatesDefinitions.h"


struct StateContext
{
	StateContext(const SortState state)
		: state(state)
	{
	}

	StateContext(const SortState state, const std::initializer_list<int> values)
		: state(state)
		, values(values)
	{
	}

	SortState state;
	std::deque<int> values;
};

class State
{
public:
	State(std::initializer_list<std::vector<ArrayElement>> arrays);

	std::vector<std::vector<ArrayElement>> getArrays() const;
	StateContext getContext() const;
	void setContext(const StateContext & stateContext);

private:
	std::vector<std::vector<ArrayElement>> arrays;
	StateContext context{SortState::NoContext, {0}};
};
