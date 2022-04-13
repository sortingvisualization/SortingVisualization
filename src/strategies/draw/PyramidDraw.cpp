#include "PyramidDraw.h"
#include "DrawHelpers.h"
#include "ofAppRunner.h"

void PyramidDraw::draw(const std::vector<ArrayElement> & array)
{
	const double drawSurfaceWidth = ofGetWindowWidth();
	const double drawSurfaceHeight = ofGetWindowHeight() * (SURFACE_HEIGHT_FACTOR - 0.1);
	const double padding = ofGetWindowHeight() * SURFACE_HEIGHT_PADDING_FACTOR * 0.5;

	const auto size = array.size();

	for(auto i = 0; i < size; ++i)
	{
		const auto ratio = array.at(i).value / static_cast<double>(size);
		const auto width = drawSurfaceWidth / size * array.at(i).value;
		const auto height = drawSurfaceHeight / size;
		const auto posX = drawSurfaceWidth / 2 - width / 2;
		const auto posY = height * i + padding;

		ofSetColor(interpolate(firstColor, secondColor, ratio));
		ofDrawRectangle(posX, posY, width, -height);
	}
}
