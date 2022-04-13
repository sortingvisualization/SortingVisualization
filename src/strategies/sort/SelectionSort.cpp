#include "SelectionSort.h"
#include "ArrayModel.h"

SelectionSort::SelectionSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void SelectionSort::sort(ArrayModel & arrayModel, const bool learningMode)
{
	if(!learningMode)
	{
		processing = true;

		future = std::async(std::launch::async, &SelectionSort::selectionSort, this, std::ref(arrayModel));
	}
	else
	{
		stateManager->setSortType(SortType::SelectionSort);
		stateManager->addState({arrayModel.getArray()});
		stateManager->setContextCurrentState({SortState::SelectionSort});

		future = std::async(std::launch::async, &SelectionSort::selectionSortLearn, this, std::ref(arrayModel));
	}
}

void SelectionSort::selectionSort(ArrayModel & model) const
{
	const auto size = model.getArraySize();
    for (int i = 0; i < size - 1; ++i) 
    {
		if(processing)
		{
		    auto lowestValueIndex = i;
		    for (int j = i + 1; j < size; ++j) 
			{
				if(processing)
				{
			        if (model.compare(lowestValueIndex, j))
					{
			            lowestValueIndex = j;
						std::this_thread::sleep_for(delay);
			        }
				}
		    }

			if(processing)
			{
				model.swap(i, lowestValueIndex);
				std::this_thread::sleep_for(delay);
			}
		}
	}
}

void SelectionSort::selectionSortLearn(ArrayModel & model) const
{
	const auto size = model.getArraySize();
    for (int i = 0; i < size - 1; ++i) 
    {
	    auto lowestValueIndex = i;
		model.setState(lowestValueIndex, ElementState::Compared);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::SelectionSortSelectFirstElement});

	    for (int j = i + 1; j < size; ++j) 
		{
			model.setState(j, ElementState::Selected);
			stateManager->addState({model.getArray()});
		    stateManager->setContextCurrentState({SortState::SelectionSortCompare,
				{model.getValueAtIndex(j), model.getValueAtIndex(lowestValueIndex)}});

	        if (model.compare(lowestValueIndex, j))
			{
				model.setState(lowestValueIndex, ElementState::Unsorted);
	            lowestValueIndex = j;
				model.setState(lowestValueIndex, ElementState::Compared);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::SelectionSortSelectNewLowestElement, {model.getValueAtIndex(lowestValueIndex)}});
	        }
			else
			{
				model.setState(j, ElementState::Unsorted);
			}
	    }

		if(i != lowestValueIndex)
		{
			model.setState(i, ElementState::Compared);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::SelectionSortSelectFirstUnsortedElement, {model.getValueAtIndex(i)}});
			model.swap(i, lowestValueIndex);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::SelectionSortSwapLowestWithUnsorted});
			model.setState(lowestValueIndex, ElementState::Unsorted);
		}
		else
		{
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::SelectionSortNoNeedSwap});
		}

		model.setState(i, ElementState::Sorted);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::SelectionSortMarkAsSorted, {model.getValueAtIndex(i)}});
	}

	model.setState(size - 1, ElementState::Sorted);
	stateManager->addState({model.getArray()});
	stateManager->setContextCurrentState({SortState::SelectionSortMarkLastAsSorted, {model.getValueAtIndex(size - 1)}});
}
