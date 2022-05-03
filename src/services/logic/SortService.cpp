#include "SortService.h"
#include "ArrayService.h"
#include "SortFactory.h"

// this service is used to delegate actions related to the sorting process
SortService::SortService(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<SortFactory> sortFactory)
	: arrayService(std::move(arrayService))
	, sortFactory(std::move(sortFactory))
{
}

SortService::~SortService()
{
	stopSorting();
}

void SortService::sort(const bool learningMode) const
{
	if (sortStrategy != nullptr)
	{
		const auto arrayModel= arrayService->getArrayModel();
		sortStrategy->sort(*arrayModel, learningMode);
	}
}

void SortService::stopSorting() const
{
	sortStrategy->stop();
}

void SortService::updateSortingSpeed(const double delayRatio) const
{
	sortStrategy->updateSpeed(delayRatio);
}

void SortService::setSortStrategy(const SortType strategy)
{
	sortStrategy = sortFactory->createSortStrategy(strategy);
}

std::shared_ptr<ISortStrategy> SortService::getSortStrategy()
{
	return sortStrategy;
}
