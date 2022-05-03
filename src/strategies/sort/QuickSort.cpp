#include "QuickSort.h"
#include "ArrayModel.h"

QuickSort::QuickSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void QuickSort::sort(ArrayModel & model, const bool learningMode)
{
	if(!learningMode)
	{
		processing = true;

		// IMPORTANT: sorting NEEDS to be done asynchronously otherwise the rendering will be stopped until the sorting is complete
		future = std::async(std::launch::async, &QuickSort::quickSort, this, std::ref(model), 0, model.getArraySize() - 1);
	}
	else
	{
		stateManager->setSortType(SortType::QuickSort);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::QuickSort});

		future = std::async(std::launch::async, &QuickSort::quickSortLearn, this, std::ref(model), 0, model.getArraySize() - 1);
	}
}

// quicksort implementation used for visualization mode
// appropriate delays (std::this_thread::sleep_for(delay);) need to be added or the sorting will finish almost instantly for smaller arrays
void QuickSort::quickSort(ArrayModel & model, const int start, const int end) const
{
	if(processing)
	{
		if (start < end)
	    {
			const auto pivot = partition(model, start, end);
			quickSort(model, start, pivot - 1);
			quickSort(model, pivot + 1, end);
	    }
	}
}

int QuickSort::partition(ArrayModel & model, const int start, const int end) const
{
	auto i = start - 1;

	for(auto j = start; j <= end - 1; ++j)
	{
		if(processing)
		{
			if(model.compare(end, j))
			{
				++i;
				model.swap(i, j);
				std::this_thread::sleep_for(delay);
			}
		}
	}

	if(processing)
	{
		std::this_thread::sleep_for(delay);
		model.swap(i + 1, end);
	}

	return (i + 1);
}

// quicksort implementation used for learning mode
// notice the setState method calls, each method call saves the current state (positions of the array elements) of a single or mutltiple arrays into a vector
// these states represent single steps of the sorting process
// there is no rule when a step should be created, it all depends how we want to represent the sorting process
// 
// IMPORTANT: together with the state an appropriate state context needs to be created, this will show an appropriate text describing the current state in the bottom-right window
// any number of values can be added optionally to the state context, they will be automatically inserted in the translation 
// example for the text: "comparing %s with %s" if we add 2 values to the state context both %s will be replaced with those values
void QuickSort::quickSortLearn(ArrayModel & model, const int start, const int end) const
{
	if (start < end)
    {
		const auto pivot = partitionLearn(model, start, end);
		quickSortLearn(model, start, pivot - 1);
		quickSortLearn(model, pivot + 1, end);
    }
	else
	{
		if(model.getArray().at(start).elementState != ElementState::Sorted)
		{
			model.setState(start, ElementState::Sorted);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::QuickSortMarkLastElementSorted});
		}
	}
}


int QuickSort::partitionLearn(ArrayModel & model, const int start, const int end) const
{
	auto i = start - 1;
	model.setState(end, ElementState::Compared);
	stateManager->addState({model.getArray()});
	stateManager->setContextCurrentState({SortState::QuickSortSelectPivotBegin});


	for(auto j = start; j < end; ++j)
	{
		model.setState(j, ElementState::Selected);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::QuickSortSelectNextElement, {model.getValueAtIndex(j)}});

		if(!model.compare(j, end))
		{
			++i;
			if(j != i)
			{
				model.setState(j, ElementState::PivotLeft);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::QuickSortMarkLowerThanPivot, {model.getValueAtIndex(j)}});

				model.setStates(i, j, ElementState::Selected);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::QuickSortSwapWithTemporaryPivot,
					{model.getValueAtIndex(j)}});

				model.swap(i, j);
				model.setState(i, ElementState::PivotLeft);
				model.setState(j, ElementState::PivotRight);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::QuickSortSwapWithTemporaryPivot,
					{model.getValueAtIndex(i)}});
			}
			else
			{
				model.setState(i, ElementState::PivotLeft);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::QuickSortMarkLowerThanPivot,
				{model.getValueAtIndex(i)}});
			}
		}
		else
		{
			model.setState(j, ElementState::PivotRight);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::QuickSortMarkHigherThanPivot,
				{model.getValueAtIndex(j)}});
		}
	}

	++i;

	if(i != end)
	{
		model.setState(end, ElementState::Selected);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::QuickSortSelectPivot,
					{model.getValueAtIndex(end)}});
		if(model.compare(i, end))
		{
			model.setState(i, ElementState::Selected);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::QuickSortSwapPivotWithTemporaryPivot});

			model.swap(i, end);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::QuickSortSwapPivotWithTemporaryPivot});

			model.setState(end, ElementState::PivotRight);
			model.setState(i, ElementState::Sorted);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::QuickSortMarkPivotAsSorted});
		}

	}
	else
	{
		model.setState(end, ElementState::Sorted);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::QuickSortAllElementsLowerThanPivot});
	}

	model.resetUnsorted();

	return i;
}
