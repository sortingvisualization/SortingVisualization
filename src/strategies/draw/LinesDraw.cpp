#include "LinesDraw.h"

void LinesDraw::draw(const std::vector<ArrayElement> & array)
{
	const double drawSurfaceWidth = getClampedWidth();
	const double drawSurfaceHeight = getClampedHeight() * SURFACE_HEIGHT_FACTOR;

	const auto width = drawSurfaceWidth / array.size();
	const auto height = drawSurfaceHeight * SURFACE_HEIGHT_FACTOR;

	for(auto i = 0; i < array.size(); ++i)
	{
		const auto ratio = array.at(i).value / static_cast<double>(array.size());
		const auto posX = width * i;
		const auto posY = drawSurfaceHeight;

		ofSetColor(interpolate(firstColor, secondColor, ratio));
		ofDrawRectangle(posX, posY, width, -height);
	}
}
