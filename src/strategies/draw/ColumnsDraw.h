#pragma once
#include "BaseDraw.h"

class ColumnsDraw : public BaseDraw
{
public:
	void draw(const std::vector<ArrayElement> &) override;
};
