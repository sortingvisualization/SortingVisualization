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
