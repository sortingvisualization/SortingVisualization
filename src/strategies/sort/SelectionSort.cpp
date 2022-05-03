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

		// IMPORTANT: sorting NEEDS to be done asynchronously otherwise the rendering will be stopped until the sorting is complete
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

// selection sort implementation used for visualization mode
// appropriate delays (std::this_thread::sleep_for(delay);) need to be added or the sorting will finish almost instantly for smaller arrays
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

// selection sort implementation used for learning mode
// notice the setState method calls, each method call saves the current state (positions of the array elements) of a single or mutltiple arrays into a vector
// these states represent single steps of the sorting process
// there is no rule when a step should be created, it all depends how we want to represent the sorting process
// 
// IMPORTANT: together with the state an appropriate state context needs to be created, this will show an appropriate text describing the current state in the bottom-right window
// any number of values can be added optionally to the state context, they will be automatically inserted in the translation 
// example for the text: "comparing %s with %s" if we add 2 values to the state context both %s will be replaced with those values
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
