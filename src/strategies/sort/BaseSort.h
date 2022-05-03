#pragma once
#include <future>

#include "ISortStrategy.h"

class BaseSort : public ISortStrategy
{
public:
	void stop() override;

	void updateSpeed(double delayRatio) override;


protected:
	std::future<void> future;

	bool processing{false};
	bool learningMode{false};
	std::chrono::nanoseconds delay{std::chrono::nanoseconds(50000000)};
};
