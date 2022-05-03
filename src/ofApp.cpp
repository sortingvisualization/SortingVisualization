#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <memory>

#include "ofApp.h"
#include "ArrayService.h"
#include "DrawService.h"
#include "DrawFactory.h"
#include "SortFactory.h"
#include "SortService.h"
#include "StateManager.h"
#include "TranslationService.h"
#include "ViewFactory.h"
#include "ViewService.h"

// creating all needed services and factories
void ofApp::setup()
{
	// default langage when launching the application can be changed here
	translationService = std::make_shared<TranslationService>(Language::Polish);
	stateManager = std::make_shared<StateManager>();
	sortFactory = std::make_shared<SortFactory>(stateManager);
	drawFactory = std::make_shared<DrawFactory>(translationService, stateManager);

	arrayService = std::make_shared<ArrayService>();
	viewService = std::make_shared<ViewService>();
	sortService = std::make_shared<SortService>(arrayService, sortFactory);
	drawService = std::make_shared<DrawService>(arrayService, viewService, drawFactory);

	viewFactory = std::make_shared<ViewFactory>(arrayService, drawService, sortService, translationService, viewService, stateManager);
	viewService->setViewFactory(viewFactory);
}

void ofApp::update()
{
}

void ofApp::draw()
{
	// this will draw all elements on screen
	// elements related to each view (IView) and also the graphical representation of the sorting process itself (IDrawStrategy)
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
