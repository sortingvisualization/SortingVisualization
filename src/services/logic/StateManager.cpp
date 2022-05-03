#include "StateManager.h"

#include "Logger.h"

// this class is used to save current states of specified arrays
// the class is used specifically for learning mode
// each state is saved into a vector and the user can navigate through those states

//add new state, you can add as many arrays as you want, check the State class constructor
void StateManager::addState(const State & state)
{
	states.emplace_back(state);
}

void StateManager::clearStates()
{
	currentStateIndex = 0;
	states.clear();
}

// returns current state
State StateManager::getCurrentState() const
{
	try
	{
		return states.at(currentStateIndex);
	}
	catch (const std::exception & ex)
	{
		logger("Failed to return state:", ex.what());
		return State{};
	}
}

// moves to next state
State StateManager::getNextState()
{
	if(currentStateIndex + 1 < states.size())
	{

		return states.at(currentStateIndex++);
	}

	return getCurrentState();
}

// moves to previous state
State StateManager::getPreviousState()
{
	if(currentStateIndex - 1 >= 0)
	{
		return states.at(currentStateIndex--);
	}

	return getCurrentState();
}

// moves to first state
State StateManager::getFirstState()
{
	currentStateIndex = 0;

	return getCurrentState();
}

// moves to last state
State StateManager::getLastState()
{
	currentStateIndex = states.size() - 1;

	return getCurrentState();
}

// checks if any state was created
bool StateManager::hasStates() const
{
	return states.size() > 0;
}

StateContext StateManager::getStateContext() const
{
	return getCurrentState().getContext();
}

// sets state context, this context can be used in different ways to display information
// in the basic implementation it's used to display text in the bottom-right window regarding the current sorting step (state)
void StateManager::setContextCurrentState(const StateContext & context)
{
	states.back().setContext(context);
}

SortType StateManager::getSortType() const
{
	return sortType;
}

void StateManager::setSortType(const SortType type)
{
	sortType = type;
}
