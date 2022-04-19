#include "ViewFactory.h"
#include "AlgorithmSelectionView.h"
#include "ArrayService.h"
#include "LearningModeView.h"
#include "ModeSelectionView.h"
#include "SortService.h"
#include "TranslationService.h"
#include "ViewService.h"
#include "VisualizationModeView.h"

ViewFactory::ViewFactory(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<DrawService> drawService, std::shared_ptr<SortService> sortService,
                         std::shared_ptr<TranslationService> translationService, std::shared_ptr<ViewService> viewService, std::shared_ptr<StateManager> stateManager)
	: arrayService(std::move(arrayService))
	, drawService(std::move(drawService))
	, sortService(std::move(sortService))
	, translationService(std::move(translationService))
	, viewService(std::move(viewService))
	, stateManager(std::move(stateManager))
{
	fillViewMap();
}

std::shared_ptr<IView> ViewFactory::createView(const ViewType strategy) const
{
	return viewToFunctorMap.at(strategy)();
}

void ViewFactory::fillViewMap()
{
	viewToFunctorMap.emplace(ViewType::AlgorithmSelectionView, [this] {
		return std::make_shared<AlgorithmSelectionView>(translationService, viewService);
	});
	viewToFunctorMap.emplace(ViewType::LearningModeView, [this] {
		return std::make_shared<LearningModeView>(arrayService, drawService, sortService, translationService, viewService, stateManager);
	});
	viewToFunctorMap.emplace(ViewType::ModeSelectionView, [this] {
		return std::make_shared<ModeSelectionView>(translationService, viewService);
	});
	viewToFunctorMap.emplace(ViewType::VisualizationModeView, [this] {
		return std::make_shared<VisualizationModeView>(arrayService, drawService, sortService, translationService, viewService);
	});
}
