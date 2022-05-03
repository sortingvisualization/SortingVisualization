#include <random>
#include <algorithm>

#include "ArrayModel.h"

// this class serves as an extension of a normal vector of integers
// the idea behind this class is to have extra information about the state of each element -> ElementState (not to confuse with general SortState)
// as an example: a general SortState will let us know that two elements are being compared in the current step so we can display an appropriate text
// however during each step we want to display much more information
// elements that are already sorted, elements that are being compared with each other, current pivot etc.
// for this purpose we use ElementState associated with each element of the array

bool ArrayModel::compare(const int firstIndex, const int secondIndex) const
{
	return array.at(firstIndex).value > array.at(secondIndex).value;
}

std::vector<ArrayElement> ArrayModel::getArray() const
{
	return array;
}

int ArrayModel::getArraySize() const
{
	return static_cast<int>(array.size());
}

int ArrayModel::getValueAtIndex(const int index) const
{
	return array.at(index).value;
}

void ArrayModel::setValueAtIndex(const int index, const int newValue)
{
	array.at(index).value = newValue;
}

void ArrayModel::modifyValueAtIndex(const int index, const int amount)
{
	array.at(index).value += amount;
}

void ArrayModel::swap(const int indexFirst, const int indexSecond)
{
	std::swap(array.at(indexFirst), array.at(indexSecond));
}

void ArrayModel::setValue(const int index, const int value)
{
	array.at(index).value = value;
}

// set state for single element
void ArrayModel::setState(const int index, const ElementState elementState)
{
	array.at(index).elementState = elementState;
}

// set state for two elements
void ArrayModel::setStates(const int firstIndex, const int secondIndex, const ElementState elementState)
{
	array.at(firstIndex).elementState = elementState;
	array.at(secondIndex).elementState = elementState;
}

// set state for elements in a specific index range
void ArrayModel::setStatesRange(const int start, const int end, const ElementState elementState)
{
	for(int i = start; i <= end; ++i)
	{
		array.at(i).elementState = elementState;
	}
}

// used when we want to keep the state of sorted elements only
void ArrayModel::resetUnsorted()
{
	for(auto & element : array)
	{
		if(element.elementState != ElementState::Sorted)
		{
			element.elementState = ElementState::Unsorted;
		}
	}
}

// initialize array with ordered data (no duplicates, every element in the given range will be created)
void ArrayModel::initializeData(const ArrayProperties & properties)
{
	std::random_device randomDevice;
    std::mt19937 engine(randomDevice());

	for(int i = 0; i < properties.arraySize; ++i)
	{
		array.emplace_back(ArrayElement{i, ElementState::Unsorted});
	}
	std::shuffle(array.begin(), array.end(), engine);

}

// initialize array with random data (can have duplicates and not every element in the given range will appear)
void ArrayModel::initializeRandomData(const ArrayProperties & properties)
{
	std::random_device randomDevice;
    std::mt19937 engine(randomDevice());
	const std::uniform_int_distribution<int> dist(1, properties.maxRange);

	for(int i = 0; i < properties.arraySize; ++i)
	{
		const auto value = properties.initializeValues ? dist(randomDevice) : 0;
		array.emplace_back(ArrayElement{value, properties.marker});
	}
	std::shuffle(array.begin(), array.end(), engine);
}
