#pragma once
#include "BaseSort.h"

class MergeSort : public BaseSort
{
public:
	MergeSort(std::shared_ptr<StateManager>);
	void sort(ArrayModel &, bool learning) override;

private:
	void mergeSort(ArrayModel &, int start, int end) const;
	void merge(ArrayModel &, int start, int mid, int end) const;
	void mergeLearn(ArrayModel &, int start, int mid, int end) const;
		
	std::shared_ptr<StateManager> stateManager;
};
