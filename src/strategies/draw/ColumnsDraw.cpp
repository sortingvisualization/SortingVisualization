#include "ColumnsDraw.h"

void ColumnsDraw::draw(const std::vector<ArrayElement> & array)
{
	const double drawSurfaceWidth = getClampedWidth();
	const double drawSurfaceHeight = getClampedHeight() * SURFACE_HEIGHT_FACTOR;
	const double columnPadding = getClampedHeight() * SURFACE_HEIGHT_PADDING_FACTOR;

	const auto width = drawSurfaceWidth / array.size();

	for(auto i = 0; i < array.size(); ++i)
	{
		const auto ratio = array.at(i).value / static_cast<double>(array.size());
		const auto height = (drawSurfaceHeight - columnPadding) / array.size() * (array.at(i).value + 1);
		const auto posX = width * i;
		const auto posY = drawSurfaceHeight;

		ofSetColor(interpolate(firstColor, secondColor, ratio));
		ofDrawRectangle(posX, posY, width, -height);
	}
}
