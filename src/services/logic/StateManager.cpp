#include "StateManager.h"

#include "Logger.h"

void StateManager::addState(const State & state)
{
	states.emplace_back(state);
}

void StateManager::clearStates()
{
	currentStateIndex = 0;
	states.clear();
}

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

State StateManager::getNextState()
{
	if(currentStateIndex + 1 < states.size())
	{

		return states.at(currentStateIndex++);
	}

	return getCurrentState();
}

State StateManager::getPreviousState()
{
	if(currentStateIndex - 1 >= 0)
	{
		return states.at(currentStateIndex--);
	}

	return getCurrentState();
}

State StateManager::getFirstState()
{
	currentStateIndex = 0;

	return getCurrentState();
}

State StateManager::getLastState()
{
	currentStateIndex = states.size() - 1;

	return getCurrentState();
}

bool StateManager::hasStates() const
{
	return states.size() > 0;
}

StateContext StateManager::getStateContext() const
{
	return getCurrentState().getContext();
}

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
