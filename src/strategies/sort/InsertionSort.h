#pragma once
#include "BaseSort.h"

class InsertionSort : public BaseSort
{
public:
	InsertionSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learningMode) override;

private:
	void insertionSort(ArrayModel &) const;
	void insertionSortLearn(ArrayModel &) const;

	std::shared_ptr<StateManager> stateManager;
};
