#pragma once
#include "Button.h"
#include "IView.h"

class TranslationService;
class ViewService;

class ModeSelectionView : public IView
{
public:
	ModeSelectionView(std::shared_ptr<TranslationService>, std::shared_ptr<ViewService>);
	~ModeSelectionView();

	void draw() override;

private:
	void getContext() override;

	void drawButtons() const;
	void drawTitle() const;

	void setup();
	void setupButtons();
	void setButtonsParameters() const;

	void onButtonPressed(std::string &);
	void onWindowResized(ofResizeEventArgs& e);

	void cleanup();

	std::shared_ptr<TranslationService> translationService;
	std::shared_ptr<ViewService> viewService;

	std::string mode;

	std::vector<std::shared_ptr<Button>> buttons;
	std::shared_ptr<Button> languageButton;
	std::string languageButtonText;
	std::vector<std::pair<std::string, ofColor>> buttonProperties;
};

