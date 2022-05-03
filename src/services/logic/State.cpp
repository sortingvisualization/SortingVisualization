#include "State.h"

// when creating a new state using StateManager we can add any number of arrays we need
// for example in merge sort we want to show the initial array and the temporary array at the same time
// in that case we pass both arrays as arguments
State::State(const std::initializer_list<std::vector<ArrayElement>> arrays) 
	: arrays(arrays)
{
}

std::vector<std::vector<ArrayElement>> State::getArrays() const
{
	return arrays;
}

StateContext State::getContext() const
{
	return context;
}

void State::setContext(const StateContext & stateContext)
{
	context = stateContext;
}
