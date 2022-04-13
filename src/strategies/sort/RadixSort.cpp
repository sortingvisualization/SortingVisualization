#include "RadixSort.h"
#include "ArrayModel.h"

RadixSort::RadixSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void RadixSort::sort(ArrayModel & model, const bool learningMode)
{
	if(!learningMode)
	{
		processing = true;

		future = std::async(std::launch::async, &RadixSort::radixSort, this, std::ref(model));
    }
    else
    {
    	stateManager->setSortType(SortType::RadixSort);
	    stateManager->addState({model.getArray(), std::vector<ArrayElement>{}, std::vector<ArrayElement>{}});
	    stateManager->setContextCurrentState({SortState::RadixSort});

		future = std::async(std::launch::async, &RadixSort::radixSortLearn,
	        this, std::ref(model));
    }
}

void RadixSort::radixSort(ArrayModel & model) const
{
    const auto values = model.getArray();
	const auto max = *std::max_element(values.begin(), values.end(), 
        [](const auto & a, const auto & b){return a.value < b.value;});

    for (int exp = 1; max.value / exp > 0; exp *= 10)
    {
    	if(processing)
        {
			countingSort(model, exp);
        }
    }
}

void RadixSort::countingSort(ArrayModel & model, const int exp) const
{
    const auto size = model.getArraySize();

	ArrayModel counts;
    counts.initializeRandomData(ArrayProperties(10, 0, ElementState::Bucket, false));

    ArrayModel output;
    output.initializeRandomData(ArrayProperties(size, 0, ElementState::Hidden, false));

    for (int i = 0; i < size; ++i)
    {
        if(processing)
        {
            counts.modifyValueAtIndex(model.getValueAtIndex(i) / exp % 10, 1);
        }
    }

    for (int i = 1; i < 10; ++i)
    {
    	if(processing)
        {
            counts.modifyValueAtIndex(i, counts.getValueAtIndex(i - 1));
        }
    }
    
    for (int i = size - 1; i >= 0; --i) 
    {
    	if(processing)
        {
            const auto positionValue = model.getValueAtIndex(i) / exp % 10;
			const auto index = counts.getValueAtIndex(positionValue) - 1;

    		counts.modifyValueAtIndex(positionValue, -1);
		    output.setValueAtIndex(index, model.getValueAtIndex(i));
        }
    }

    for (int i = 0; i < size; ++i)
    {
    	if(processing)
        {
    		model.setValue(i, output.getValueAtIndex(i));
	        std::this_thread::sleep_for(delay);
        }
    }
}

void RadixSort::radixSortLearn(ArrayModel & model) const
{
    const auto values = model.getArray();
    const auto max = *std::max_element(values.begin(), values.end(), 
        [](const auto & a, const auto & b){return a.value < b.value;});

    for (int exp = 1; max.value > exp; exp *= 10)
    {
    	countingSortLearn(model, exp);
    }

    stateManager->addState({model.getArray(), std::vector<ArrayElement>{}, std::vector<ArrayElement>{}});
    stateManager->setContextCurrentState({SortState::Sorted});
}

void RadixSort::countingSortLearn(ArrayModel & model, const int exp) const
{
    const auto size = model.getArraySize();
    model.setStatesRange(0, size - 1, ElementState::Unsorted);

    ArrayModel counts;
    counts.initializeRandomData(ArrayProperties(10, 0, ElementState::Bucket, false));

    ArrayModel output;
    output.initializeRandomData(ArrayProperties(size, 0, ElementState::Hidden, false));

    const auto getStates = [&model, &counts, &output]{
	    return State{model.getArray(), counts.getArray(), output.getArray()};
    };

    for (int i = 0; i < size; ++i)
    {
        const auto positionValue = model.getValueAtIndex(i) / exp % 10;

        model.setState(i, ElementState::Selected); 
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectNextElement, {model.getValueAtIndex(i), positionValue}});

        counts.setState(positionValue, ElementState::Selected);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectBucket, {positionValue}});

        counts.modifyValueAtIndex(positionValue, 1);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortIncrementCount, {positionValue}});

        counts.setState(positionValue, ElementState::Bucket);
        model.setState(i, ElementState::Unsorted);
    }

    for (int i = 1; i < 10; ++i)
    {
        counts.setStates(i, i - 1, ElementState::BucketSum);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectBuckets});

        counts.modifyValueAtIndex(i, counts.getValueAtIndex(i - 1));
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSumCount, {counts.getValueAtIndex(i)}});

    	counts.setStates(i, i - 1, ElementState::Bucket);
    }

    output.setStatesRange(0, output.getArraySize() - 1, ElementState::Unsorted);
    stateManager->addState(getStates());
	stateManager->setContextCurrentState({SortState::RadixSortCopyValues});

    for (int i = size - 1; i >= 0; --i) 
    {
        const auto positionValue = model.getValueAtIndex(i) / exp % 10;
        const auto index = counts.getValueAtIndex(positionValue) - 1;

        model.setState(i, ElementState::Selected);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectNextElement, {model.getValueAtIndex(i), positionValue}});

        counts.setState(positionValue, ElementState::Selected);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectBucket, {positionValue}});

        counts.modifyValueAtIndex(positionValue, -1);
        stateManager->addState(getStates());
    	stateManager->setContextCurrentState({SortState::RadixSortDecrementCount});

        output.setState(index, ElementState::Selected);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortSelectOutgoing, {index}});

    	output.setValueAtIndex(index, model.getValueAtIndex(i));
        model.setState(i, ElementState::Unsorted);
        counts.setState(positionValue, ElementState::Bucket);
        output.setState(index, ElementState::Sorted);
        stateManager->addState(getStates());
        stateManager->setContextCurrentState({SortState::RadixSortMoveToTemporaryArray, {index}});
    }

	output.setStatesRange(0, output.getArraySize() - 1, ElementState::Selected);
    stateManager->addState(getStates());
	stateManager->setContextCurrentState({SortState::RadixSortCopyValuesBack});

	model.setStatesRange(0, output.getArraySize() - 1, ElementState::Selected);
    stateManager->addState(getStates());
	stateManager->setContextCurrentState({SortState::RadixSortCopyValuesBack});

    for (int i = 0; i < size; ++i)
    {
        model.setValue(i, output.getValueAtIndex(i));
    	output.setState(i, ElementState::Hidden);
    }

    counts.setStatesRange(0, counts.getArraySize() - 1, ElementState::Hidden);
    model.setStatesRange(0, model.getArraySize() - 1, ElementState::Sorted);
	stateManager->addState(getStates());
	stateManager->setContextCurrentState({SortState::RadixSortCopyValuesBack});
}
