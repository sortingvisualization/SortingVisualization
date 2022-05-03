#include "BaseSort.h"

namespace 
{
// this value was determined empirically, there might be a better value
constexpr auto BASE_DELAY_VALUE = std::chrono::nanoseconds(50000000);
}

// base sorting class where common logic is executed

// sets processing flag to false, when implementing an algorithm in visualization mode this flag should be checked every possible step
// this will allow to terminate the sorting thread very quickly
void BaseSort::stop()
{
	processing = false;
}

// updates delay speed
void BaseSort::updateSpeed(const double delayRatio)
{
	auto ratio = delayRatio;
	if(delayRatio == 1.0)
	{
		// we don't want to have a value of 1.0 because in most cases the sorting will finish almost instantly
		ratio -= 0.01;
	}

	// there might be a better formula especially for arrays of bigger sizes.
	// it works well for sizes of around few thousand elements and below but for bigger arrays it's too slow (at 1.0 it still sorts the array instantly using good algorithms)
	const int newDelay = static_cast<int>(BASE_DELAY_VALUE.count() * (1 - ratio));
	delay = std::chrono::nanoseconds(newDelay);
}
