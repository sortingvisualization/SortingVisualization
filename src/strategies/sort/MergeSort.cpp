#include "MergeSort.h"
#include "ArrayModel.h"
#include "Logger.h"

MergeSort::MergeSort(std::shared_ptr<StateManager> stateManager)
	: stateManager(std::move(stateManager))
{
}

void MergeSort::sort(ArrayModel & model, const bool learning)
{
	learningMode = learning;

	if(!learningMode)
	{
		processing = true;
	}
	else
	{
		stateManager->setSortType(SortType::MergeSort);
		stateManager->addState({model.getArray(), std::vector<ArrayElement>{}});
		stateManager->setContextCurrentState({SortState::MergeSort});
	}

	// IMPORTANT: sorting NEEDS to be done asynchronously otherwise the rendering will be stopped until the sorting is complete
	future = std::async(std::launch::async, &MergeSort::mergeSort, this, std::ref(model), 0, model.getArraySize() - 1);
}

void MergeSort::mergeSort(ArrayModel & model, const int start, const int end) const
{
	if(start < end)
	{
		const int mid = (start + end) / 2;
		mergeSort(model, start, mid);
		mergeSort(model, mid+1, end);
		if(!learningMode)
		{
			merge(model, start, mid, end);
		}
		else
		{
			mergeLearn(model, start, mid, end);
		}
	}
}

// merge sort implementation used for visualization mode
// appropriate delays (std::this_thread::sleep_for(delay);) need to be added or the sorting will finish almost instantly for smaller arrays
void MergeSort::merge(ArrayModel & arrayModel, const int start, const int mid, const int end) const
{
	std::vector<int> values;
	int i = start;
	int j = mid + 1;

	while (processing && (i <= mid && j <= end))
	{
		if(!arrayModel.compare(i, j))
		{
			values.emplace_back(arrayModel.getValueAtIndex(i++));
		}
		else
		{
			values.emplace_back(arrayModel.getValueAtIndex(j++));
		}
	}
	while(processing && i <= mid)
	{
		values.emplace_back(arrayModel.getValueAtIndex(i++));
	}
	  
	while (processing && j <= end) 
	{
		values.emplace_back(arrayModel.getValueAtIndex(j++));
	}
	
	for(i = start; i <= end; ++i)
	{
		if(processing)
		{
			arrayModel.setValue(i, values.at(i - start));
			std::this_thread::sleep_for(delay);
		}
	}
}

// merge sort implementation used for learning mode
// notice the setState method calls, each method call saves the current state (positions of the array elements) of a single or mutltiple arrays into a vector
// these states represent single steps of the sorting process
// there is no rule when a step should be created, it all depends how we want to represent the sorting process
// 
// IMPORTANT: together with the state an appropriate state context needs to be created, this will show an appropriate text describing the current state in the bottom-right window
// any number of values can be added optionally to the state context, they will be automatically inserted in the translation 
// example for the text: "comparing %s with %s" if we add 2 values to the state context both %s will be replaced with those values
void MergeSort::mergeLearn(ArrayModel & model, const int start, const int mid, const int end) const
{
	std::vector<ArrayElement> values;
	values.resize(model.getArraySize());
	for(auto & value : values)
	{
		value.elementState = ElementState::Hidden;
	}
	int i = start;
	int j = mid + 1;
	int subArrayIndex = start;

	model.setStatesRange(start, mid, ElementState::MergeLeftPart);
	model.setStatesRange(mid+1, end, ElementState::MergeRightPart);
	stateManager->addState({model.getArray(), values});
	stateManager->setContextCurrentState({SortState::MergeSortMarkParts});

	while (i <= mid && j <= end)
	{
		if(!model.compare(i, j))
		{
			model.setState(i, ElementState::Selected);
			stateManager->addState({model.getArray(), values});
			stateManager->setContextCurrentState({SortState::MergeSortSelectLowestValue});

			values.at(subArrayIndex) = model.getArray().at(i);
			model.setState(i, ElementState::Hidden);
			stateManager->addState({model.getArray(), values});
			stateManager->setContextCurrentState({SortState::MergeSortTemporarilyCopy, {model.getValueAtIndex(i)}});

			++i;
			++subArrayIndex;
		}
		else
		{
			model.setState(j, ElementState::Selected);
			stateManager->addState({model.getArray(), values});
			stateManager->setContextCurrentState({SortState::MergeSortSelectLowestValue});

			values.at(subArrayIndex) = model.getArray().at(j);
			model.setState(j, ElementState::Hidden);
			stateManager->addState({model.getArray(), values});
			stateManager->setContextCurrentState({SortState::MergeSortTemporarilyCopy, {model.getValueAtIndex(j)}});

			++j;
			++subArrayIndex;
		}
	}

	while(i <= mid)
	{
		model.setState(i, ElementState::Selected);
		stateManager->addState({model.getArray(), values});
		stateManager->setContextCurrentState({SortState::MergeSortSelectLowestValue});

		values.at(subArrayIndex) = model.getArray().at(i);
		model.setState(i, ElementState::Hidden);
		stateManager->addState({model.getArray(), values});
		stateManager->setContextCurrentState({SortState::MergeSortTemporarilyCopy, {model.getValueAtIndex(i)}});

		++i;
		++subArrayIndex;
	}
	  
	while (j <= end) 
	{
		model.setState(j, ElementState::Selected);
		stateManager->addState({model.getArray(), values});
		stateManager->setContextCurrentState({SortState::MergeSortSelectLowestValue});

		values.at(subArrayIndex) = model.getArray().at(j);
		model.setState(j, ElementState::Hidden);
		stateManager->addState({model.getArray(), values});
		stateManager->setContextCurrentState({SortState::MergeSortTemporarilyCopy, {model.getValueAtIndex(j)}});

		++j;
		++subArrayIndex;
	}
	
	for(i = start; i <= end; ++i)
	{
		model.setValue(i, values.at(i).value);
		model.setState(i, ElementState::Sorted);
		values.at(i).elementState = ElementState::Hidden;
		stateManager->addState({model.getArray(), values});
		const auto size = model.getArraySize();

		if(end - start == size - 1 && i == size -1)
		{
			stateManager->setContextCurrentState({SortState::Sorted});
		}
		else
		{
			stateManager->setContextCurrentState({SortState::MergeSortCopyBack});
		}
	}
}
