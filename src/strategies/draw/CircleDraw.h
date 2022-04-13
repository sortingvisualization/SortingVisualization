#pragma once
#include "BaseDraw.h"

class CircleDraw : public BaseDraw
{
public:
	void draw(const std::vector<ArrayElement> &) override;
};
