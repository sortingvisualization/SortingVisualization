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
