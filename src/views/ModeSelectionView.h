#pragma once
#include "Button.h"
#include "IView.h"

class ViewService;

class ModeSelectionView : public IView
{
public:
	ModeSelectionView(std::shared_ptr<ViewService>);
	~ModeSelectionView();

	void draw() override;

private:
	void getContext() override;

	void drawButtons() const;

	void setup();
	void setupButtons();
	void setButtonsParameters() const;

	void onButtonPressed(std::string &);
	void onWindowResized(ofResizeEventArgs& e);

	void cleanup();

	std::shared_ptr<ViewService> viewService;

	std::string mode;

	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::pair<std::string, ofColor>> buttonsColors;
};

