#include "BubbleSort.h"
#include "ArrayModel.h"

BubbleSort::BubbleSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void BubbleSort::sort(ArrayModel & model, const bool learningMode)
{
	if(!learningMode)
	{
		processing = true;

		// IMPORTANT: sorting NEEDS to be done asynchronously otherwise the rendering will be stopped until the sorting is complete
		future = std::async(std::launch::async, &BubbleSort::bubbleSort, this, std::ref(model));
	}
	else
	{
		stateManager->setSortType(SortType::BubbleSort);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::BubbleSort});

		future = std::async(std::launch::async, &BubbleSort::bubbleSortLearn, this, std::ref(model));
	}
}

// bubble sort implementation used for visualization mode
// appropriate delays (std::this_thread::sleep_for(delay);) need to be added or the sorting will finish almost instantly for smaller arrays
void BubbleSort::bubbleSort(ArrayModel & model) const
{
	const auto size = model.getArraySize();

	for(int i = 0; i < size - 1; i++)
	{
		if(processing)
		{
			for(int j = 0; j < size - i - 1; j++)
			{
				if(processing && model.compare(j, j+1))
				{
					model.swap((j), j+1);
					std::this_thread::sleep_for(delay);
				}
			}
		}
	}
}

// bubble sort implementation used for learning mode
// notice the setState method calls, each method call saves the current state (positions of the array elements) of a single or mutltiple arrays into a vector
// these states represent single steps of the sorting process
// there is no rule when a step should be created, it all depends how we want to represent the sorting process
// 
// IMPORTANT: together with the state an appropriate state context needs to be created, this will show an appropriate text describing the current state in the bottom-right window
// any number of values can be added optionally to the state context, they will be automatically inserted in the translation 
// example for the text: "comparing %s with %s" if we add 2 values to the state context both %s will be replaced with those values
void BubbleSort::bubbleSortLearn(ArrayModel & model) const
{
	const auto size = model.getArraySize();

	for(int i = 0; i < size - 1; ++i)
	{
		const auto boundsIndex = size - i - 1; 
		for(int j = 0; j < boundsIndex; ++j)
		{
			model.setStates(j, j+1, ElementState::Selected);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::BubbleSortCompare,
				{model.getValueAtIndex(j), model.getValueAtIndex(j+1)}});

			if(model.compare(j, j+1))
			{
				model.swap((j), j+1);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::BubbleSortSwap,
					{model.getValueAtIndex(j+1), model.getValueAtIndex(j)}});
			}
			model.setStates(j, j+1, ElementState::Unsorted);
		}

		if(boundsIndex != 1)
		{
			model.setState(boundsIndex, ElementState::Sorted);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::BubbleSortLastElementSorted,
			{model.getValueAtIndex(boundsIndex)}});
		}
		else
		{
			model.setStates(0, boundsIndex, ElementState::Sorted);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::BubbleSortLastElementsSorted,
			{model.getValueAtIndex(0), model.getValueAtIndex(boundsIndex)}});
		}
	}
}
