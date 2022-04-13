#pragma once
#include "BaseSort.h"

class RadixSort : public BaseSort
{
public:
	RadixSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learningMode) override;

private:
	void countingSort(ArrayModel &, int exp) const;
	void radixSort(ArrayModel &) const;
	void countingSortLearn(ArrayModel &, int exp) const;
	void radixSortLearn(ArrayModel &) const;
			
	std::shared_ptr<StateManager> stateManager;
};
