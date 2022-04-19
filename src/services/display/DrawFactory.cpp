#include "DrawFactory.h"
#include "CircleDraw.h"
#include "ColumnsDraw.h"
#include "LearningDraw.h"
#include "PyramidDraw.h"
#include "StateManager.h"
#include "LinesDraw.h"
#include "TranslationService.h"

DrawFactory::DrawFactory(std::shared_ptr<TranslationService> translationService, std::shared_ptr<StateManager> stateManager)
	: translationService(std::move(translationService))
	, stateManager(std::move(stateManager))
{
	fillStrategyMap();
}

std::shared_ptr<IDrawStrategy> DrawFactory::createDrawStrategy(const DrawType strategy) const
{
	return strategyToFunctorMap.at(strategy)();
}

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
