#pragma once
#include "IDrawStrategy.h"
#include "DrawDefinitions.h"
#include "OfHelpers.h"
#include "DrawHelpers.h"

class BaseDraw : public IDrawStrategy
{
public:
	void updateFirstColor(const ofColor &) override;
	void updateSecondColor(const ofColor &) override;

protected:
	ofColor firstColor;
	ofColor secondColor;
};

