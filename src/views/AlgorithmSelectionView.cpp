#include "AlgorithmSelectionView.h"

#include "Logger.h"
#include "SortDefinitions.h"
#include "TranslationService.h"
#include "ViewService.h"

namespace
{
std::map<Tc, std::string> sortTranslationToConstMap =
{
	{Tc::SortBubble, BUBBLE_SORT},
	{Tc::SortInsertion, INSERTION_SORT},
	{Tc::SortMerge, MERGE_SORT},
	{Tc::SortQuick, QUICK_SORT},
	{Tc::SortRadix, RADIX_SORT},
	{Tc::SortSelection, SELECTION_SORT},
};
}

AlgorithmSelectionView::AlgorithmSelectionView(std::shared_ptr<TranslationService> translationService, std::shared_ptr<ViewService> viewService)
	: translationService(std::move(translationService))
	, viewService(std::move(viewService))
{
	setup();
}

AlgorithmSelectionView::~AlgorithmSelectionView()
{
	cleanup();
}

// main method to draw all ui elements
void AlgorithmSelectionView::draw()
{
	drawTitle();
	drawButtons();
}

// selecting an algorithm on this view will change the view either to LearningModeView VisualiuzationModeView
// this is determined based on the context. The below context is set on the ModeSelectionView
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

// draw title text
void AlgorithmSelectionView::drawTitle() const
{
	const auto titlePosX = ofGetWindowWidth() * 0.5;
	const auto titlePosY = ofGetWindowHeight() * 0.1;

	const auto bounds = titleFont.getStringBoundingBox(titleText, 0, 0);
	const auto offset = ofVec2f( std::floor(-bounds.x - bounds.width * 0.5), std::floor(-bounds.y - bounds.height * 0.5) );

	ofPushStyle();
	ofSetColor(titleTextColor);
	titleFont.drawString(titleText, titlePosX + offset.x, titlePosY + offset.y);
	ofPopStyle();
}

// creating listeners will allow to call a class method based on certain events. 
// in the example below: onWindowResized will be called when the window gets resized. "windowResized" is a built in event in openFrameworks.
void AlgorithmSelectionView::setup()
{
	ofAddListener(ofEvents().windowResized, this, &AlgorithmSelectionView::onWindowResized);

	getContext();
	if (mode == translationService->getTranslation(Tc::ModeLearning))
	{
		titleTextColor = ofColor(0,0,0);
		ofBackground(ofColor(225,225,225));
	}
	else if (mode == translationService->getTranslation(Tc::ModeVisualization))
	{
		titleTextColor = ofColor(225,225,225);
		ofBackground(ofColor(0,0,0));
	}

	setupButtons();
	setupTitle();
}

void AlgorithmSelectionView::setupButtons()
{
	buttonsProperties =
	{
		{translationService->getTranslation(Tc::SortBubble), ofColor(255, 102, 178)},
		{translationService->getTranslation(Tc::SortInsertion), ofColor(102, 255, 102)},
		{translationService->getTranslation(Tc::SortMerge), ofColor(255, 153, 51)},
		{translationService->getTranslation(Tc::SortQuick), ofColor(102, 178, 255)},
		{translationService->getTranslation(Tc::SortRadix), ofColor(255, 102, 102)},
		{translationService->getTranslation(Tc::SortSelection), ofColor(153, 51, 255)},
	};

	for (const auto & property : buttonsProperties)
	{
		const auto button = std::make_shared<Button>(0, 0, 0, 0);
		button->setText(property.first);
		button->setBackgroundColor(property.second);
		ofAddListener(button->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);

		buttons.emplace_back(button);
	}

	setupBackButton();
	setButtonsParameters();
}

void AlgorithmSelectionView::setupBackButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(translationService->getTranslation(Tc::ButtonBack));
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
}

// the method will be called on setup and after the window is resized.
// this will allow to resize the buttons based on the application's window size.
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


void AlgorithmSelectionView::setupTitle()
{
	const auto titleFontSize = (ofGetWindowHeight() / 35 + ofGetWindowWidth() / 35) / 2;
	titleText = translationService->getTranslation(Tc::SortAlgorithms);
	titleFont.load("mono.ttf", titleFontSize);
}

void AlgorithmSelectionView::onButtonPressed(std::string & str)
{
	if (str == translationService->getTranslation(Tc::ButtonBack))
	{
		viewService->clearContext();
		viewService->setCurrentView(ViewType::ModeSelectionView);
	}
	else
	{
		try
		{
			const auto it = std::find_if(sortTranslationToConstMap.begin(), sortTranslationToConstMap.end(), [&str, this](const auto & element)
			{
				return translationService->getTranslation(element.first) == str;
			});
			// we add context here so the next screen will know which sorting algorithm was selected
			viewService->addToContext(SORT_CONTEXT, sortTranslationToConstMap.at(it->first));
			
		}
		catch (const std::exception & ex)
		{
			logger("Invalid sort type");
		}

		// Setting next view based on context
		if(mode == translationService->getTranslation(Tc::ModeLearning))
		{
			viewService->setCurrentView(ViewType::LearningModeView);
		}
		else if(mode == translationService->getTranslation(Tc::ModeVisualization))
		{
			viewService->setCurrentView(ViewType::VisualizationModeView);
		}
	}
}

// resize both buttons and title on this view after the window size has changed
void AlgorithmSelectionView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
	setupTitle();
}

// all listeners need to be removed when the class object is destroyed (when switching views for example). Otherwise the application will crash.
void AlgorithmSelectionView::cleanup()
{
	ofRemoveListener(ofEvents().windowResized, this, &AlgorithmSelectionView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
	}

	ofRemoveListener(backButton->clickedInside, this, &AlgorithmSelectionView::onButtonPressed);
}
