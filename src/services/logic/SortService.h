#pragma once
#include <memory>
#include <vector>

#include "SortDefinitions.h"

class ArrayService;
class ISortStrategy;
class SortFactory;

class SortService
{
public:
	explicit SortService(std::shared_ptr<ArrayService>, std::shared_ptr<SortFactory>);
	~SortService();

	void sort(bool learningMode) const;
	void stopSorting() const;
	void updateSortingSpeed(double delayRatio) const;
	void setSortStrategy(SortType);
	std::shared_ptr<ISortStrategy> getSortStrategy();

private:
	std::shared_ptr<ArrayService> arrayService;
	std::shared_ptr<SortFactory> sortFactory;

	std::shared_ptr<ISortStrategy> sortStrategy;
};
