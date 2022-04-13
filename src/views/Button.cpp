#include "Button.h"
#include "ofGraphics.h"

Button::Button(const double x, const double y, const double w, const double h)
	: shape(x, y, w, h)
{
	ofRegisterMouseEvents(this);
	font.load("mono.ttf", fontSize);
}

Button::~Button()
{
	ofUnregisterMouseEvents(this);
}

void Button::draw() const
{
	ofPushStyle();
	if(borderSet)
	{
		auto borderShape = shape;
		borderShape.width += 4;
		borderShape.height += 4;
		borderShape.x -= 2;
		borderShape.y -= 2;
		ofSetColor(borderColor);
		ofDrawRectangle(borderShape);
	}
	const auto color = isPressed ? highlightColor : backgroundColor;
	ofSetColor(color);
	ofDrawRectangle(shape);
	drawCenteredText();
	ofPopStyle();
}

void Button::setShape(const ofRectangle & newShape)
{
	shape = newShape;
}

void Button::setPosition(const double x, const double y)
{
	shape.setPosition(x, y);
}

ofRectangle Button::getPosition() const
{
	return shape;
}

void Button::setSize(const double w, const double h)
{
	shape.setSize(w, h);
}

void Button::setText(const std::string& text)
{
	buttonText = text;
}

std::string Button::getText()
{
	return buttonText;
}

void Button::setBackgroundColor(const ofColor color)
{
	backgroundColor = color;
	highlightColor = color - ofColor(30, 30, 30);
}

void Button::setBorderColor(const ofColor color)
{
	borderSet = true;
	borderColor = color;
}

void Button::setTextColor(const ofColor color)
{
	textColor = color;
}

void Button::setFontSize(const int size)
{
	fontSize = size;
	reloadFont();
}

void Button::mouseMoved(ofMouseEventArgs &)
{
}

void Button::mouseDragged(ofMouseEventArgs &)
{
}

void Button::mousePressed(ofMouseEventArgs & args)
{
	if (shape.inside(args))
	{
		isPressed = true;
    }
}

void Button::mouseReleased(ofMouseEventArgs & args)
{
	if(isPressed)
	{
		isPressed = false;
		if (shape.inside(args))
		{
	        ofNotifyEvent(clickedInside, buttonText, this); 
	    }
	}
}

void Button::mouseScrolled(ofMouseEventArgs &)
{
}

void Button::mouseEntered(ofMouseEventArgs &)
{
}

void Button::mouseExited(ofMouseEventArgs &)
{
}

void Button::reloadFont()
{
	font.load("mono.ttf", fontSize);
}

void Button::drawCenteredText() const
{
	const auto bounds = font.getStringBoundingBox(buttonText, 0, 0);
	const auto offset = ofVec2f( std::floor(-bounds.x - bounds.width * 0.5), std::floor(-bounds.y - bounds.height * 0.5) );

	const auto posX = shape.x + shape.width / 2;
	const auto posY = shape.y + shape.height / 2;

	ofSetColor(textColor);
	font.drawString(buttonText, posX + offset.x, posY + offset.y);
}
