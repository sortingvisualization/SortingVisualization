#pragma once
#include "BaseDraw.h"

class LinesDraw : public BaseDraw
{
public:
	void draw(const std::vector<ArrayElement> &) override;
};
