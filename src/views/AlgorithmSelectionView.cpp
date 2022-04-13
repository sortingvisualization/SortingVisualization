#include "AlgorithmSelectionView.h"
#include "ViewService.h"
#include "SortDefinitions.h"

AlgorithmSelectionView::AlgorithmSelectionView(std::shared_ptr<ViewService> viewService)
	: viewService(std::move(viewService))
{
	setup();
}

AlgorithmSelectionView::~AlgorithmSelectionView()
{
	cleanup();
}

void AlgorithmSelectionView::draw()
{
	drawButtons();
}

void AlgorithmSelectionView::getContext()
{
	if(viewService->keyExists(MODE_CONTEXT))
	{
		mode = viewService->getValue(MODE_CONTEXT);
	}
}

void AlgorithmSelectionView::drawButtons() const
{
	for(const auto & button : buttons)
	{
		button->draw();
	}

	backButton->draw();
}

void AlgorithmSelectionView::setup()
{
	ofAddListener(ofEvents().windowResized, this, &AlgorithmSelectionView::onWindowResized);

	getContext();
	if (mode == LEARNING_MODE)
	{
		ofBackground(ofColor(225,225,225));
	}
	else if (mode == VISUALIZATION_MODE)
	{
		ofBackground(ofColor(0,0,0));
	}

	setupButtons();
}

void AlgorithmSelectionView::setupButtons()
{
	buttonsColors =
	{
		{BUBBLE_SORT, ofColor(255, 102, 178)},
		{INSERTION_SORT, ofColor(102, 255, 102)},
		{MERGE_SORT, ofColor(255, 153, 51)},
		{QUICK_SORT, ofColor(102, 178, 255)},
		{RADIX_SORT, ofColor(255, 102, 102)},
		{SELECTION_SORT, ofColor(153, 51, 255)},
	};

	for (const auto & color : buttonsColors)
	{
		const auto button = std::make_shared<Button>(0, 0, 0, 0);
		button->setText(color.first);
		button->setBackgroundColor(color.second);
		ofAddListener(button->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);

		buttons.emplace_back(button);
	}

	setupBackButton();
	setButtonsParameters();
}

void AlgorithmSelectionView::setupBackButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(BACK_BUTTON_LABEL);
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
}

void AlgorithmSelectionView::setButtonsParameters() const
{
	const int buttonsCount = buttons.size();

	const double windowWidth = ofGetWindowWidth();
	const double windowHeight = ofGetWindowHeight();
	double buttonWidth = windowWidth * 0.3;
	double buttonHeight = windowHeight * 0.15;
	auto fontSize = (ofGetWindowWidth() / 50 + ofGetScreenHeight() / 50) / 2;


	for(int i = 0; i < buttonsCount; ++i)
	{
		const int row = i % (buttonsCount / 2);
		const int column = i / (buttonsCount / 2);
		const double buttonX = windowWidth * 0.15 + windowWidth * 0.4 * column;
		const double buttonY = windowHeight * 0.2 + windowHeight * 0.2 * row;
		
		buttons.at(i)->setShape(ofRectangle(buttonX, buttonY, buttonWidth, buttonHeight));

		buttons.at(i)->setFontSize(fontSize);
	}

	fontSize = (ofGetWindowWidth() / 60 + ofGetScreenHeight() / 60) / 2;
	buttonWidth = windowWidth * 0.05 - 5;
	buttonHeight = windowHeight * 0.05;

	backButton->setPosition(0, windowHeight - buttonHeight * 2);
	backButton->setSize(buttonWidth * 2, buttonHeight);
	backButton->setFontSize(fontSize);
}

void AlgorithmSelectionView::onButtonPressed(std::string & str)
{
	viewService->addToContext(SORT_CONTEXT, str);
	if (str == BACK_BUTTON_LABEL)
	{
		viewService->clearContext();
		viewService->setCurrentView(ViewType::ModeSelectionView);
	}

	else if(mode == LEARNING_MODE)
	{
		viewService->setCurrentView(ViewType::LearningModeView);
	}
	else if(mode == VISUALIZATION_MODE)
	{
		viewService->setCurrentView(ViewType::VisualizationModeView);
	}
}

void AlgorithmSelectionView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
}

void AlgorithmSelectionView::cleanup()
{
	ofRemoveListener(ofEvents().windowResized, this, &AlgorithmSelectionView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
	}

	ofRemoveListener(backButton->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
}
