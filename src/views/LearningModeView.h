#pragma once
#include "Button.h"
#include "IView.h"

class ArrayService;
class DrawService;
class SortService;
class StateManager;
class TranslationService;
class ViewService;

class LearningModeView : public IView
{
public:
	LearningModeView(std::shared_ptr<ArrayService>, std::shared_ptr<DrawService>, std::shared_ptr<SortService>, 
		std::shared_ptr<TranslationService>, std::shared_ptr<ViewService>, std::shared_ptr<StateManager>);
	~LearningModeView();

	void draw() override;

private:
	void getContext() override;

	void drawButtons() const;

	void setup();
	void setupButtons();
	void setupBackButton();
	void setupResetButton();
	void setButtonsParameters() const;

	void sortSetup();
	void onButtonPressed(std::string & str);
	void onKeyPressed(ofKeyEventArgs &);
	void onWindowResized(ofResizeEventArgs &);

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
	std::vector<std::shared_ptr<Button>> buttons;
	std::shared_ptr<Button> backButton;
	std::shared_ptr<Button> resetButton;
};
