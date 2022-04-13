#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
	ofGLFWWindowSettings settings;
	settings.resizable = false;
	settings.setSize(1280, 720);
	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
