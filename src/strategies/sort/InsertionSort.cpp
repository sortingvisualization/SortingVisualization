#include "InsertionSort.h"
#include "ArrayModel.h"

InsertionSort::InsertionSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void InsertionSort::sort(ArrayModel & model, const bool learningMode)
{
	if(!learningMode)
	{
		processing = true;

		// IMPORTANT: sorting NEEDS to be done asynchronously otherwise the rendering will be stopped until the sorting is complete
		future = std::async(std::launch::async, &InsertionSort::insertionSort, this, std::ref(model));
	}
	else
	{
		stateManager->setSortType(SortType::InsertionSort);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::InsertionSort});

		future = std::async(std::launch::async, &InsertionSort::insertionSortLearn, this, std::ref(model));
	}

}

// insertion sort implementation used for visualization mode
// appropriate delays (std::this_thread::sleep_for(delay);) need to be added or the sorting will finish almost instantly for smaller arrays
void InsertionSort::insertionSort(ArrayModel & model) const
{
	for(int i = 1; i < model.getArraySize(); ++i)
	{
		if(processing)
		{
			int position = i;

			while(processing && (position > 0 && !model.compare(position, position-1)))
			{
				model.swap(position, position-1);
				--position;
				std::this_thread::sleep_for(delay);
			}
		}
	}
}

// insertion sort implementation used for learning mode
// notice the setState method calls, each method call saves the current state (positions of the array elements) of a single or mutltiple arrays into a vector
// these states represent single steps of the sorting process
// there is no rule when a step should be created, it all depends how we want to represent the sorting process
// 
// IMPORTANT: together with the state an appropriate state context needs to be created, this will show an appropriate text describing the current state in the bottom-right window
// any number of values can be added optionally to the state context, they will be automatically inserted in the translation 
// example for the text: "comparing %s with %s" if we add 2 values to the state context both %s will be replaced with those values
void InsertionSort::insertionSortLearn(ArrayModel & model) const
{
	model.setState(0, ElementState::Sorted);
	stateManager->addState({model.getArray()});
	stateManager->setContextCurrentState({SortState::InsertionSortFirstElementSorted,
						{model.getValueAtIndex(0)}});

	for(int i = 1; i < model.getArraySize(); ++i)
	{
		int position = i;

		model.setState(i, ElementState::Selected);
		stateManager->addState({model.getArray()});
		stateManager->setContextCurrentState({SortState::InsertionSortSelectElement,
					{model.getValueAtIndex(i)}});

		while(position > 0)
		{
			if(!model.compare(position - 1, position))
			{
				model.setStates(position - 1, position, ElementState::Selected);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::InsertionSortCompare,
						{model.getValueAtIndex(position - 1), model.getValueAtIndex(position)}});

				model.setStates(position - 1, position, ElementState::Sorted);
				stateManager->addState({model.getArray()});
				stateManager->setContextCurrentState({SortState::InsertionSortPrevLower,
						{model.getValueAtIndex(position - 1), model.getValueAtIndex(position)}});
				break;
			}

			model.setStates(position - 1, position, ElementState::Selected);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::InsertionSortCompare,
					{model.getValueAtIndex(position - 1), model.getValueAtIndex(position)}});

			model.swap(position, position-1);
			stateManager->addState({model.getArray()});
			stateManager->setContextCurrentState({SortState::InsertionSortSwap,
					{model.getValueAtIndex(position - 1), model.getValueAtIndex(position)}});

			model.setStates(position, position - 1, ElementState::Sorted);
			--position;
		}
	}

	model.setStatesRange(0, model.getArraySize() - 1, ElementState::Sorted);
	stateManager->addState({model.getArray()});
	stateManager->setContextCurrentState({SortState::Sorted});
}
