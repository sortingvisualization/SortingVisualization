#pragma once
#include <vector>

enum class ElementState
{
	Unsorted,
	Sorted,
	Selected,
	Compared,
	MergeLeftPart,
	MergeRightPart,
	PivotLeft,
	PivotRight,
	Bucket,
	BucketSum,
	Hidden,
};

struct ArrayElement
{
	int value;
	ElementState elementState;
};

struct ArrayProperties
{
	ArrayProperties(const int arraySize, const int maxRange = 50, const ElementState marker = ElementState::Unsorted, const bool initializeValues = true)
		: arraySize(arraySize)
		, maxRange(maxRange)
		, marker(marker)
		, initializeValues(initializeValues)
	{
	}

	int arraySize;
	int maxRange;
	ElementState marker;
	bool initializeValues;
};

class ArrayModel
{
public:
	void initializeData(const ArrayProperties &);
	void initializeRandomData(const ArrayProperties &);

	bool compare(int firstIndex, int secondIndex) const;
	std::vector<ArrayElement> getArray() const;
	int getArraySize() const;
	int getValueAtIndex(int index) const;
	void setValueAtIndex(int index, int newValue);
	void modifyValueAtIndex(int index, int amount);
	void swap(int indexFirst, int indexSecond);
	void setValue(int index, int value);
	void setState(int index, ElementState);
	void setStates(int firstIndex, int secondIndex, ElementState);
	void setStatesRange(int start, int end, ElementState);
	void resetUnsorted();

private:
	std::vector<ArrayElement> array;
};
