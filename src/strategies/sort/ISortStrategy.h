#pragma once
#include "StateManager.h"

class ArrayModel;

class ISortStrategy
{
public:
	virtual void sort(ArrayModel &, bool learningMode) = 0;
	virtual void stop() = 0;

	virtual void updateSpeed(double delayRatio) = 0;
};
