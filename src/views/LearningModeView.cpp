#include "LearningModeView.h"

#include "ArrayModel.h"
#include "ArrayService.h"
#include "DrawService.h"
#include "SortDefinitions.h"
#include "SortService.h"
#include "ViewService.h"
#include "StateManager.h"
#include "TranslationService.h"

LearningModeView::LearningModeView(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<DrawService> drawService, std::shared_ptr<SortService> sortService, 
                                   std::shared_ptr<TranslationService> translationService, std::shared_ptr<ViewService> viewService, std::shared_ptr<StateManager> stateManager)
	: arrayService(std::move(arrayService))
	, drawService(std::move(drawService))
	, sortService(std::move(sortService))
	, translationService(std::move(translationService))
	, viewService(std::move(viewService))
	, stateManager(std::move(stateManager))
{
	setup();
}

LearningModeView::~LearningModeView()
{
	cleanup();
}

void LearningModeView::draw()
{
	if(!uiHidden)
	{
		drawButtons();
	}
}

void LearningModeView::getContext()
{
	if(viewService->keyExists(SORT_CONTEXT))
	{
		sortType = viewService->getValue(SORT_CONTEXT);
	}

	if(viewService->keyExists(MODE_CONTEXT))
	{
		mode = viewService->getValue(MODE_CONTEXT);
	}
}

void LearningModeView::drawButtons() const
{
	for(const auto & button : buttons)
	{
		button->draw();
	}

	backButton->draw();
	resetButton->draw();
}

void LearningModeView::setup()
{
	ofAddListener(ofEvents().keyPressed, this, &LearningModeView::onKeyPressed);
	ofAddListener(ofEvents().windowResized, this, &LearningModeView::onWindowResized);

	getContext();
	setupButtons();

	if(nameToSortTypeMap.find(sortType) != nameToSortTypeMap.end())
	{
		sortService->setSortStrategy(nameToSortTypeMap.at(sortType));
		sortSetup();
	}

	drawService->setDrawStrategy(DrawType::LearningDraw);
	drawService->updateArray();
}

void LearningModeView::setupButtons()
{
	const std::vector<std::string> buttonsLabels =
	{
		FIRST_BUTTON_LABEL,
		PREV_BUTTON_LABEL,
		NEXT_BUTTON_LABEL,
		LAST_BUTTON_LABEL
	};

	for (const auto & buttonsLabel : buttonsLabels)
	{
		const auto button = std::make_shared<Button>(0, 0, 0, 0);
		button->setText(buttonsLabel);
		button->setBackgroundColor(ofColor(75, 101, 186));

		ofAddListener(button->clickedInside, this, &LearningModeView::onButtonPressed);

		buttons.emplace_back(button);
	}

	setupBackButton();
	setupResetButton();
	setButtonsParameters();
}

void LearningModeView::setupBackButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(translationService->getTranslation(Tc::ButtonBack));
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &LearningModeView::onButtonPressed);
}

void LearningModeView::setupResetButton()
{
	resetButton = std::make_shared<Button>(0, 0, 0, 0);
	resetButton->setText(translationService->getTranslation(Tc::ButtonReset));
	resetButton->setBackgroundColor(ofColor(83, 188, 104));

	ofAddListener(resetButton->clickedInside, this, &LearningModeView::onButtonPressed);
}

void LearningModeView::setButtonsParameters() const
{
	const auto windowWidth = ofGetWindowWidth();
	const auto windowHeight = ofGetWindowHeight();
	const auto buttonWidth = windowWidth * 0.05 - 5;
	const auto buttonHeight = windowHeight * 0.05;
	const auto size = buttons.size();
	const auto fontSize = (ofGetWindowWidth() / 60 + ofGetScreenHeight() / 60) / 2;

	for(int i = 0; i < size; ++i)
	{
		const auto offsetX = windowWidth * 0.5 - size * (buttonWidth + BUTTON_PADDING) * 0.5;
		const auto posX = (buttonWidth + BUTTON_PADDING) * i + offsetX;
		const auto posY = windowHeight - buttonHeight * 2;

		buttons.at(i)->setPosition(posX, posY);
		buttons.at(i)->setSize(buttonWidth, buttonHeight);
		buttons.at(i)->setFontSize(fontSize);
	}


	backButton->setPosition(0, windowHeight - buttonHeight * 2);
	backButton->setSize(buttonWidth * 2, buttonHeight);
	backButton->setFontSize(fontSize);

	resetButton->setPosition(buttonWidth * 2 + buttonWidth * 0.1, windowHeight - buttonHeight * 2);
	resetButton->setSize(buttonWidth * 2, buttonHeight);
	resetButton->setFontSize(fontSize);
}

void LearningModeView::onButtonPressed(std::string & str)
{
	if(!uiHidden)
	{
		if(str == PREV_BUTTON_LABEL)
		{
			stateManager->getPreviousState();
		}
		else if(str == NEXT_BUTTON_LABEL)
		{
			stateManager->getNextState();
		}
		else if(str == FIRST_BUTTON_LABEL)
		{
			stateManager->getFirstState();
		}
		else if(str == LAST_BUTTON_LABEL)
		{
			stateManager->getLastState();
		}
		else if (str == translationService->getTranslation(Tc::ButtonBack))
		{
			drawService->stopDrawing();
			viewService->addToContext(MODE_CONTEXT, mode);
			viewService->setCurrentView(ViewType::AlgorithmSelectionView);
		}
		else if (str == translationService->getTranslation(Tc::ButtonReset))
		{
			sortSetup();
		}
	}
}

void LearningModeView::sortSetup()
{
	stateManager->clearStates();
	arrayService->initializeArray(ArrayProperties(ofRandom(5, 20), 50), true);
	sortService->sort(true);
}

void LearningModeView::onKeyPressed(ofKeyEventArgs & ev)
{
	if (ev.key == OF_KEY_LEFT)
	{
		stateManager->getPreviousState();
	}
	else if (ev.key == OF_KEY_RIGHT)
	{
		stateManager->getNextState();
	}
	else if (ev.key == OF_KEY_DOWN)
	{
		stateManager->getFirstState();
	}
	else if (ev.key == OF_KEY_UP)
	{
		stateManager->getLastState();
	}
	else if (ev.key == OF_KEY_BACKSPACE)
	{
		drawService->stopDrawing();
		viewService->addToContext(MODE_CONTEXT, mode);
		viewService->setCurrentView(ViewType::AlgorithmSelectionView);
	}
	else if (ev.key == 'r')
	{
		sortSetup();
	}
	else if (ev.key == 'h')
	{
		uiHidden = !uiHidden;
	}
}

void LearningModeView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
}

void LearningModeView::cleanup()
{
	ofRemoveListener(ofEvents().keyPressed, this, &LearningModeView::onKeyPressed);
	ofRemoveListener(ofEvents().windowResized, this, &LearningModeView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &LearningModeView::onButtonPressed);
	}

	ofRemoveListener(backButton->clickedInside, this, &LearningModeView::onButtonPressed);
}
