#pragma once
#include "ofGraphics.h"

class IView
{
public:
	virtual void draw() = 0;
	virtual void getContext() = 0;
};