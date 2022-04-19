#pragma once
#include <map>
#include <functional>
#include <memory>

#include "IDrawStrategy.h"
#include "DrawDefinitions.h"

using DrawStrategy = std::function<std::shared_ptr<IDrawStrategy>()>;
class StateManager;
class TranslationService;

class DrawFactory
{
public:
	DrawFactory(std::shared_ptr<TranslationService>, std::shared_ptr<StateManager>);
	std::shared_ptr<IDrawStrategy> createDrawStrategy(DrawType) const;

private:
	void fillStrategyMap();

	std::shared_ptr<TranslationService> translationService;
	std::shared_ptr<StateManager> stateManager;
	std::map<DrawType, DrawStrategy> strategyToFunctorMap;
};
