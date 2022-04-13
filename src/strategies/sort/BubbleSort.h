#pragma once
#include "BaseSort.h"

class StateManager;

class BubbleSort : public BaseSort
{
public:
	BubbleSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learningMode) override;

private:
	void bubbleSort(ArrayModel &) const;
	void bubbleSortLearn(ArrayModel &) const;

	std::shared_ptr<StateManager> stateManager;
};
