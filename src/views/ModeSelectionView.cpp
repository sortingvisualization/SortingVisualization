#include "ModeSelectionView.h"

#include "ViewService.h"

ModeSelectionView::ModeSelectionView(std::shared_ptr<ViewService> viewService)
	: viewService(std::move(viewService))
{
	setup();
}

ModeSelectionView::~ModeSelectionView()
{
	cleanup();
}

void ModeSelectionView::draw()
{
	drawButtons();
}

void ModeSelectionView::getContext()
{
}

void ModeSelectionView::drawButtons() const
{
	for(const auto & button : buttons)
	{
		button->draw();
	}
}

void ModeSelectionView::setup()
{
	ofBackground(ofColor(225,225,225));
	ofAddListener(ofEvents().windowResized, this, &ModeSelectionView::onWindowResized);

	setupButtons();
}

void ModeSelectionView::setupButtons()
{
	buttonsColors =
	{
		{LEARNING_MODE, ofColor(102, 178, 255)},
		{VISUALIZATION_MODE, ofColor(0, 0, 102)},
	};

	for(const auto & color : buttonsColors)
	{
		const auto button = std::make_shared<Button>(0, 0, 0, 0);
		button->setText(color.first);
		button->setBackgroundColor(color.second);
		ofAddListener(button->clickedInside, this, &ModeSelectionView::onButtonPressed);

		buttons.emplace_back(button);
	}

	setButtonsParameters();
}

void ModeSelectionView::setButtonsParameters() const
{
	const int buttonsCount = buttons.size();

	const double windowWidth = ofGetWindowWidth();
	const double windowHeight = ofGetWindowHeight();
	const double buttonWidth = windowWidth * 0.3;
	const double buttonHeight = windowHeight * 0.3;

	for(int i = 0; i < buttonsCount; ++i)
	{
		const int column = i / (buttonsCount / 2);
		const double buttonX = windowWidth * 0.2 + windowWidth * 0.3 * column;
		const double buttonY = windowHeight * 0.3;
		
		buttons.at(i)->setShape(ofRectangle(buttonX, buttonY, buttonWidth, buttonHeight));

		const auto fontSize = (ofGetWindowWidth() / 50 + ofGetScreenHeight() / 50) / 2;
		buttons.at(i)->setFontSize(fontSize);
	}
}

void ModeSelectionView::onButtonPressed(std::string & str)
{
	viewService->addToContext(MODE_CONTEXT, str);
	viewService->setCurrentView(ViewType::AlgorithmSelectionView);
}

void ModeSelectionView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
}

void ModeSelectionView::cleanup()
{
	ofRemoveListener(ofEvents().windowResized, this, &ModeSelectionView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &ModeSelectionView::onButtonPressed);
	}
}
