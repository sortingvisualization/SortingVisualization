#include "BaseSort.h"

namespace 
{
constexpr auto BASE_DELAY_VALUE = std::chrono::nanoseconds(50000000);
}

void BaseSort::stop()
{
	processing = false;
}

void BaseSort::updateSpeed(const double delayRatio)
{
	auto ratio = delayRatio;
	if(delayRatio == 1.0)
	{
		ratio -= 0.01;
	}
	const int newDelay = static_cast<int>(BASE_DELAY_VALUE.count() * (1 - ratio));
	delay = std::chrono::nanoseconds(newDelay);
}

bool BaseSort::isProcessing()
{
	if(future.valid())
	{
		const auto status = future.wait_for(std::chrono::milliseconds(0));
		if(status == std::future_status::ready)
		{
			processing = false;
		}
	}

	return processing;
}
