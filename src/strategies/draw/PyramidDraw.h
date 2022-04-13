#pragma once
#include "BaseDraw.h"

class PyramidDraw : public BaseDraw
{
public:
	void draw(const std::vector<ArrayElement> &) override;
};
