#include "SortFactory.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"

//The purpose of this factory is to allow to set/change the sorting algorithm used for sorting
SortFactory::SortFactory(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
	fillStrategyMap();
}

//Allows to create objects which inherit from ISortStrategy(interface/base class) during runtime based on the specified enum value.
//For example calling createSortStrategy(SortType::InsertionSort) (key = SortType::InsertionSort)
//will create an object of InsertionSort class (value = return std::make_shared<InsertionSort>(stateManager);).
// 
//It is necessary to remember to stop the sorting process(SortingService class) before changing the sorting strategy.
std::shared_ptr<ISortStrategy> SortFactory::createSortStrategy(const SortType strategy) const
{
	return strategyToFunctorMap.at(strategy)();
}

//Fills the map with objects
//key = SortType
//value = std::function which returns a ISortStrategy class object
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
