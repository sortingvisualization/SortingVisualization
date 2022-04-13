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
