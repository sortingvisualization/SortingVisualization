#pragma once
#include <algorithm>

#include "ofAppRunner.h"

namespace
{
int getClampedHeight()
{
	return std::max(0, ofGetWindowHeight());
}

int getClampedWidth()
{
	return std::max(0, ofGetWindowWidth());
}
}