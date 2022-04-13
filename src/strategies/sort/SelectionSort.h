#pragma once
#include "BaseSort.h"

class SelectionSort : public BaseSort
{
public:

	SelectionSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learningMode) override;

private:
	void selectionSort(ArrayModel & model) const;
	void selectionSortLearn(ArrayModel & model) const;

	std::shared_ptr<StateManager> stateManager;
};
