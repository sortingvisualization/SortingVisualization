#include "SortFactory.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"

SortFactory::SortFactory(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
	fillStrategyMap();
}

std::shared_ptr<ISortStrategy> SortFactory::createSortStrategy(const SortType strategy) const
{
	return strategyToFunctorMap.at(strategy)();
}

void SortFactory::fillStrategyMap()
{
	strategyToFunctorMap.emplace(SortType::BubbleSort, [this] {
		return std::make_shared<BubbleSort>(stateManager);
	});
	strategyToFunctorMap.emplace(SortType::InsertionSort, [this] {
		return std::make_shared<InsertionSort>(stateManager);
	});
	strategyToFunctorMap.emplace(SortType::MergeSort, [this] {
		return std::make_shared<MergeSort>(stateManager);
	});
	strategyToFunctorMap.emplace(SortType::QuickSort, [this] {
		return std::make_shared<QuickSort>(stateManager);
	});
	strategyToFunctorMap.emplace(SortType::RadixSort, [this] {
		return std::make_shared<RadixSort>(stateManager);
	});
	strategyToFunctorMap.emplace(SortType::SelectionSort, [this] {
		return std::make_shared<SelectionSort>(stateManager);
	});
}
