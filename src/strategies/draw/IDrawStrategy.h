#pragma once
#include <vector>

#include "ofGraphics.h"
#include "State.h"

class IDrawStrategy
{
public:
	virtual void draw(const std::vector<ArrayElement> &) = 0;
	virtual void updateFirstColor(const ofColor &) = 0;
	virtual void updateSecondColor(const ofColor &) = 0;
};
