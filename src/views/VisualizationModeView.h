#pragma once
#include "Button.h"
#include "IView.h"
#include "ofxGuiExtended.h"
#include "SortDefinitions.h"

class ArrayService;
class DrawService;
class SortService;
class StateManager;
class TranslationService;
class ViewService;

class VisualizationModeView : public IView
{
public:
	VisualizationModeView(std::shared_ptr<ArrayService>, std::shared_ptr<DrawService>, std::shared_ptr<SortService>, 
		std::shared_ptr<TranslationService>, std::shared_ptr<ViewService>);
	~VisualizationModeView();

	void draw() override;

private:
	void getContext() override;

	void drawButtons() const;

	void setup();
	void setupButtons();
	void setupBackButton();
	void setupSortResetButton();
	void setButtonsParameters() const;

	void setupDrawMethodsGroup();
	void setupPropertiesParams();
	void setupPropertiesGroup();
	void setupSpeedControl();
	void setupColors();

	void arraySetup() const;

	void onArraySizeChanged(int & size);
	void onSortSpeedChanged(float & delayRatio);
	void onButtonPressed(std::string & str);
	void onDrawTypeChanged(int & index);
	void onFirstColorChanged(ofColor & color);
	void onSecondColorChanged(ofColor & color);
	void onKeyPressed(ofKeyEventArgs &);
	void onWindowResized(ofResizeEventArgs &);

	void minimizeGroups() const;
	void cleanup();

	std::shared_ptr<ArrayService> arrayService;
	std::shared_ptr<DrawService> drawService;
	std::shared_ptr<SortService> sortService;
	std::shared_ptr<TranslationService> translationService;
	std::shared_ptr<ViewService> viewService;
	std::shared_ptr<StateManager> stateManager;

	std::string sortType;
	std::string mode;

	bool uiHidden{false};
	int arraySize{DEFAULT_ARRAY_SIZE_VISUALIZATION_MODE};

	std::vector<std::shared_ptr<Button>> buttons;
	std::shared_ptr<Button> backButton;
	std::shared_ptr<Button> sortResetButton;

	ofxGui gui;

	ofxGuiGroup *drawMethodsGroup{nullptr};
	ofParameterGroup drawMethodsParams;
	int currentDrawIndex{1};

	ofxGuiGroup *propertiesGroup{nullptr};
	ofParameterGroup propertiesParams;
	ofParameter<int> arraySizeParam;
	ofParameter<ofColor> firstColorParam;
	ofParameter<ofColor> secondColorParam;

	ofxGuiGroup *speedGroup{nullptr};
	ofParameterGroup speedParams;
	ofParameter<float> speedParam;
};
