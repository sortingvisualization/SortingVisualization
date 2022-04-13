#include "ofGraphics.h"

namespace
{
int linearInterpolation(const int a, const int b, const double ratio)
{
    return a * (1 - ratio) + b * ratio;
}
ofColor interpolate(const ofColor & from, const ofColor & to, const double ratio)
{
	float hueFrom;
	float saturationFrom;
	float brightnessFrom;
	from.getHsb(hueFrom, saturationFrom, brightnessFrom);

	float hueTo;
	float saturationTo;
	float brightnessTo;
	to.getHsb(hueTo, saturationTo, brightnessTo);

    const double resultHue = linearInterpolation(hueFrom, hueTo, ratio);
    const double resultSaturation = linearInterpolation(saturationFrom, saturationTo, ratio);
    const double resultBrightness = linearInterpolation(brightnessFrom, brightnessTo, ratio);

    return ofColor::fromHsb(resultHue, resultSaturation, resultBrightness);
}
}
