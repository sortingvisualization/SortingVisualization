#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <memory>

#include "ofApp.h"
#include "ArrayService.h"
#include "DrawService.h"
#include "DrawFactory.h"
#include "SortFactory.h"
#include "SortService.h"
#include "StateManager.h"
#include "ViewFactory.h"
#include "ViewService.h"


void ofApp::setup()
{
	stateManager = std::make_shared<StateManager>();
	sortFactory = std::make_shared<SortFactory>(stateManager);
	drawFactory = std::make_shared<DrawFactory>(stateManager);

	arrayService = std::make_shared<ArrayService>();
	viewService = std::make_shared<ViewService>();
	sortService = std::make_shared<SortService>(arrayService, sortFactory);
	drawService = std::make_shared<DrawService>(arrayService, viewService, drawFactory);

	viewFactory = std::make_shared<ViewFactory>(arrayService, drawService, sortService, viewService, stateManager);
	viewService->setViewFactory(viewFactory);
}

void ofApp::update()
{
}

void ofApp::draw()
{
	drawService->draw();
}

void ofApp::keyPressed(int key)
{
	if(key == 'f')
	{
		ofToggleFullscreen();
	}
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
