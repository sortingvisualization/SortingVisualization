#pragma once
#include "ofTrueTypeFont.h"

class Button
{
public:
	Button(double x, double y, double w, double h);
	~Button();

	void draw() const;

	void setShape(const ofRectangle &);
	void setPosition(double x, double y);
	ofRectangle getPosition() const;
	void setSize(double w, double h);
	void setText(const std::string & text);
	std::string getText();
	void setBackgroundColor(ofColor);
	void setBorderColor(ofColor);
	void setTextColor(ofColor);
	void setFontSize(int size);

	void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);
    void mouseEntered(ofMouseEventArgs & args);
    void mouseExited(ofMouseEventArgs & args);

	ofEvent<std::string> clickedInside;

private:
	void reloadFont();
	void drawCenteredText() const;

	ofRectangle shape;
	bool isPressed{false};
	bool borderSet{false};

	ofColor backgroundColor{0, 0, 0};
	ofColor borderColor{0, 0, 0};
	ofColor highlightColor{0, 0, 0};
	ofColor textColor{255, 255, 255};
	int fontSize{24};

	ofTrueTypeFont font;
	std::string buttonText;
};
