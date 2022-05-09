#include <cmath>

#include "CircleDraw.h"

void CircleDraw::draw(const std::vector<ArrayElement> & array)
{
	const double drawSurfaceWidth = getClampedWidth();
	const double drawSurfaceHeight = getClampedHeight() * SURFACE_HEIGHT_FACTOR;
	const double columnPadding = getClampedHeight() * SURFACE_HEIGHT_PADDING_FACTOR;

	const auto posX1 = drawSurfaceWidth / 2;
	const auto posY1 = drawSurfaceHeight / 2 + columnPadding / 4;

	const auto size = array.size();

	for(auto i = 0; i < size; ++i)
	{
		const auto ratio = array.at(i).value / static_cast<double>(array.size());
		const auto rad = 2 * PI / size * i;
		const auto radNext = 2 * PI / size * (i + 1);

		const auto sinValue = sin(rad);
		const auto cosValue = cos(rad);
		const auto sinValueNext = sin(radNext);
		const auto cosValueNext = cos(radNext);

		const auto length = drawSurfaceHeight / 2 - columnPadding * 0.4;

		const auto posX2 = posX1 + length * sinValue;
		const auto posY2 = posY1 + length * cosValue;
		const auto posX3 = posX1 + length * sinValueNext;
		const auto posY3 = posY1 + length * cosValueNext;

		ofSetColor(interpolate(firstColor, secondColor, ratio));
		ofDrawTriangle(posX1, posY1, posX2, posY2, posX3, posY3);
	}
}
