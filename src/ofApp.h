#pragma once

#include <memory>

#include "ofMain.h"

class ArrayService;
class DrawService;
class GuiService;
class SortService;
class ViewService;

class StateManager;
class SortFactory;
class DrawFactory;
class ViewFactory;

class ofApp : public ofBaseApp
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void mouseMoved(int x, int y) override;
	void mouseDragged(int x, int y, int button) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
	void mouseEntered(int x, int y) override;
	void mouseExited(int x, int y) override;
	void windowResized(int w, int h) override;
	void dragEvent(ofDragInfo dragInfo) override;
	void gotMessage(ofMessage msg) override;

private:
	std::shared_ptr<ArrayService> arrayService;
	std::shared_ptr<DrawService> drawService;
	std::shared_ptr<GuiService> guiService;
	std::shared_ptr<SortService> sortService;
	std::shared_ptr<ViewService> viewService;

	std::shared_ptr<StateManager> stateManager;
	std::shared_ptr<SortFactory> sortFactory;
	std::shared_ptr<DrawFactory> drawFactory;
	std::shared_ptr<ViewFactory> viewFactory;

};
