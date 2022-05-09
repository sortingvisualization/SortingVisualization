#include "ModeSelectionView.h"

#include "TranslationService.h"
#include "ViewService.h"

namespace
{
std::map<Language, Tc> languageToTranslationMap =
{
	{Language::English, Tc::LanguageEnglish},
	{Language::Polish, Tc::LanguagePolish},
};
}

ModeSelectionView::ModeSelectionView(std::shared_ptr<TranslationService> translationService, std::shared_ptr<ViewService> viewService)
	: translationService(std::move(translationService))
	, viewService(std::move(viewService))
{
	setup();
}

ModeSelectionView::~ModeSelectionView()
{
	cleanup();
}

// this draws all ui elements
void ModeSelectionView::draw()
{
	drawButtons();
}

// this is the main menu screen, getting context is not needed
void ModeSelectionView::getContext()
{
}

void ModeSelectionView::drawButtons() const
{
	for(const auto & button : buttons)
	{
		button->draw();
	}

	languageButton->draw();
}


void ModeSelectionView::setup()
{
	ofBackground(ofColor(225,225,225));
	ofAddListener(ofEvents().windowResized, this, &ModeSelectionView::onWindowResized);

	setupButtons();
}

// create buttons for mode selection and changing the language
void ModeSelectionView::setupButtons()
{
	buttons.clear();

	buttonProperties =
	{
		{translationService->getTranslation(Tc::ModeLearning), ofColor(102, 178, 255)},
		{translationService->getTranslation(Tc::ModeVisualization), ofColor(0, 0, 102)},
	};

	for(const auto & property : buttonProperties)
	{
		const auto button = std::make_shared<Button>(0, 0, 0, 0);
		button->setText(property.first);
		button->setBackgroundColor(property.second);
		ofAddListener(button->clickedInside, this, &ModeSelectionView::onButtonPressed);

		buttons.emplace_back(button);
	}

	languageButton = std::make_shared<Button>(0, 0, 0, 0);
	const auto nextLanguage = translationService->getNextLanguage();
	languageButton->setText(translationService->getTranslation(languageToTranslationMap.at(nextLanguage)));
	languageButton->setBackgroundColor(ofColor(102, 178, 255));
	ofAddListener(languageButton->clickedInside, this, &ModeSelectionView::onButtonPressed);

	setButtonsParameters();
}

// the method will be called on setup and after the window is resized.
// this will allow to resize the buttons based on the application's window size.
void ModeSelectionView::setButtonsParameters() const
{
	const int buttonsCount = buttons.size();

	const double windowWidth = getClampedWidth();
	const double windowHeight = getClampedHeight();
	const double buttonWidth = windowWidth * 0.3;
	const double buttonHeight = windowHeight * 0.3;

	const auto fontSize = (getClampedWidth() / 50 + getClampedHeight() / 50) / 2;


	for(int i = 0; i < buttonsCount; ++i)
	{
		const int column = i / (buttonsCount / 2);
		const double buttonX = windowWidth * 0.2 + windowWidth * 0.3 * column;
		const double buttonY = windowHeight * 0.3;
		
		buttons.at(i)->setShape(ofRectangle(buttonX, buttonY, buttonWidth, buttonHeight));
		buttons.at(i)->setFontSize(fontSize);
	}

	const auto languageButtonWidth = windowWidth * 0.15;
	const auto languageButtonHeight = windowHeight * 0.15;

	languageButton->setShape(ofRectangle((windowWidth - languageButtonWidth), (windowHeight - languageButtonHeight), languageButtonWidth, languageButtonHeight));
	languageButton->setFontSize(fontSize);
}

// handle button events
void ModeSelectionView::onButtonPressed(std::string & str)
{
	if(str == translationService->getTranslation(Tc::LanguageEnglish))
	{
		translationService->loadLanguage(Language::English);
		setupButtons();
	}
	else if(str == translationService->getTranslation(Tc::LanguagePolish))
	{
		translationService->loadLanguage(Language::Polish);
		setupButtons();
	}
	else
	{
		// we need to add mode context so on the next screen there is information which mode was selected
		viewService->addToContext(MODE_CONTEXT, str);
		viewService->setCurrentView(ViewType::AlgorithmSelectionView);
	}
}

// resize buttons on this view after the window size has changed
void ModeSelectionView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
}

// all listeners need to be removed when the class object is destroyed (when switching views for example). Otherwise the application will crash.
void ModeSelectionView::cleanup()
{
	ofRemoveListener(ofEvents().windowResized, this, &ModeSelectionView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &ModeSelectionView::onButtonPressed);
	}

	ofRemoveListener(languageButton->clickedInside, this, &ModeSelectionView::onButtonPressed);
}
