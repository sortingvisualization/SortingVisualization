#pragma once
#include <map>
#include <functional>
#include <memory>

#include "ISortStrategy.h"
#include "SortDefinitions.h"

using SortStrategy = std::function<std::shared_ptr<ISortStrategy>()>;
class StateManager;

class SortFactory
{
public:
	SortFactory(std::shared_ptr<StateManager>);
	std::shared_ptr<ISortStrategy> createSortStrategy(SortType) const;

private:
	void fillStrategyMap();

	std::shared_ptr<StateManager> stateManager;
	std::map<SortType, SortStrategy> strategyToFunctorMap;
};
