#include "State.h"

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
