#pragma once
#include "BaseSort.h"

class QuickSort : public BaseSort
{
public:
	QuickSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learningMode) override;

private:
	void quickSort(ArrayModel &, int start, int end) const;
	int partition(ArrayModel &, int start, int end) const;
	void quickSortLearn(ArrayModel &, int start, int end) const;
	int partitionLearn(ArrayModel &, int start, int end) const;
	
	std::shared_ptr<StateManager> stateManager;
};
