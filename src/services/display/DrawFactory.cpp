#include "DrawFactory.h"
#include "CircleDraw.h"
#include "ColumnsDraw.h"
#include "LearningDraw.h"
#include "PyramidDraw.h"
#include "StateManager.h"
#include "LinesDraw.h"
#include "TranslationService.h"

//The purpose of this factory is to allow to set/change the way we draw arrays and the sorting process on the screen
DrawFactory::DrawFactory(std::shared_ptr<TranslationService> translationService, std::shared_ptr<StateManager> stateManager)
	: translationService(std::move(translationService))
	, stateManager(std::move(stateManager))
{
	fillStrategyMap();
}

//Allows to create objects which inherit from IDrawStrategy(interface/base class) during runtime based on the specified enum value.
//For example calling createDrawStrategy(DrawType::CircleDraw) (key = DrawType::CircleDraw)
//will create an object of CircleDraw class (value = return std::make_shared<CircleDraw>();).
// 
//We can dynamically change the way we draw arrays without interrupting the sorting process itself.
std::shared_ptr<IDrawStrategy> DrawFactory::createDrawStrategy(const DrawType strategy) const
{
	return strategyToFunctorMap.at(strategy)();
}

//Fills the map with objects
//key = DrawType
//value = std::function which returns a IDrawStrategy class object
void DrawFactory::fillStrategyMap()
{
	strategyToFunctorMap.emplace(DrawType::LearningDraw, [this] {
		return std::make_shared<LearningDraw>(translationService, stateManager);
	});
	strategyToFunctorMap.emplace(DrawType::CircleDraw, [] {
		return std::make_shared<CircleDraw>();
	});
	strategyToFunctorMap.emplace(DrawType::ColumnsDraw, [] {
		return std::make_shared<ColumnsDraw>();
	});
	strategyToFunctorMap.emplace(DrawType::LinesDraw, [] {
		return std::make_shared<LinesDraw>();
	});
	strategyToFunctorMap.emplace(DrawType::PyramidDraw, [] {
		return std::make_shared<PyramidDraw>();
	});
}
