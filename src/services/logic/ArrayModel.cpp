#include <random>
#include <algorithm>

#include "ArrayModel.h"

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

void ArrayModel::setState(const int index, const ElementState elementState)
{
	array.at(index).elementState = elementState;
}

void ArrayModel::setStates(const int firstIndex, const int secondIndex, const ElementState elementState)
{
	array.at(firstIndex).elementState = elementState;
	array.at(secondIndex).elementState = elementState;
}

void ArrayModel::setStatesRange(const int start, const int end, const ElementState elementState)
{
	for(int i = start; i <= end; ++i)
	{
		array.at(i).elementState = elementState;
	}
}

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
