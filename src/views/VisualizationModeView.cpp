#include "VisualizationModeView.h"

#include "ArrayModel.h"
#include "ArrayService.h"
#include "DrawService.h"
#include "GuiConsts.h"
#include "IDrawStrategy.h"
#include "Logger.h"
#include "SortDefinitions.h"
#include "SortService.h"
#include "TranslationService.h"
#include "ViewService.h"

namespace
{
std::map<std::string, Tc> drawConstToTranslationMap =
{
	{CIRCLE_DRAW, Tc::DrawCircle},
	{COLUMNS_DRAW, Tc::DrawColumns},
	{LINES_DRAW, Tc::DrawLines},
	{PYRAMID_DRAW, Tc::DrawPyramid},
};
}

VisualizationModeView::VisualizationModeView(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<DrawService> drawService, 
	std::shared_ptr<SortService> sortService, std::shared_ptr<TranslationService> translationService, std::shared_ptr<ViewService> viewService)
	: arrayService(std::move(arrayService))
	, drawService(std::move(drawService))
	, sortService(std::move(sortService))
	, translationService(std::move(translationService))
	, viewService(std::move(viewService))
{
	setup();
}

VisualizationModeView::~VisualizationModeView()
{
	cleanup();
}

void VisualizationModeView::draw()
{
	if(!uiHidden)
	{
		drawButtons();
	}
}

void VisualizationModeView::getContext()
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

void VisualizationModeView::drawButtons() const
{
	for(const auto & button : buttons)
	{
		button->draw();
	}

	backButton->draw();
	sortResetButton->draw();
}

void VisualizationModeView::setup()
{
	ofAddListener(ofEvents().keyPressed, this, &VisualizationModeView::onKeyPressed);
	ofAddListener(ofEvents().windowResized, this, &VisualizationModeView::onWindowResized);

	getContext();
	setupButtons();
	setButtonsParameters();

	if(nameToSortTypeMap.find(sortType) != nameToSortTypeMap.end())
	{
		sortService->setSortStrategy(nameToSortTypeMap.at(sortType));
	}
	else
	{
		sortService->setSortStrategy(SortType::BubbleSort);
	}

	setupColors();
	arraySetup();
}

void VisualizationModeView::setupButtons()
{
	setupBackButton();
	setupSortResetButton();
	setupDrawMethodsGroup();
	setupPropertiesParams();
	setupPropertiesGroup();
	setupSpeedControl();
}

void VisualizationModeView::setupBackButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(translationService->getTranslation(Tc::ButtonBack));
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &VisualizationModeView::onButtonPressed);
}

void VisualizationModeView::setupSortResetButton()
{
	sortResetButton = std::make_shared<Button>(0, 0, 0, 0);
	sortResetButton->setText(translationService->getTranslation(Tc::ButtonSort));
	sortResetButton->setBackgroundColor(ofColor(83, 188, 104));

	ofAddListener(sortResetButton->clickedInside, this, &VisualizationModeView::onButtonPressed);
}

void VisualizationModeView::setButtonsParameters() const
{
	const auto screenWidth = ofGetWindowWidth();
	const auto screenHeight = ofGetWindowHeight();
	const auto buttonWidth = screenWidth * 0.05 - 5;
	const auto buttonHeight = screenHeight * 0.05;
	const auto fontSize = (ofGetWindowWidth() / 60 + ofGetScreenHeight() / 60) / 2;

	backButton->setPosition(0, screenHeight - buttonHeight * 2);
	backButton->setSize(buttonWidth * 2, buttonHeight);
	backButton->setFontSize(fontSize);

	sortResetButton->setPosition(buttonWidth * 2 + buttonWidth * 0.1, screenHeight - buttonHeight * 2);
	sortResetButton->setSize(buttonWidth * 2, buttonHeight);
	sortResetButton->setFontSize(fontSize);
}

void VisualizationModeView::setupDrawMethodsGroup()
{
	drawMethodsParams.setName(translationService->getTranslation(Tc::DrawMethod));
	for (const auto & strategy : drawService->getDrawTypes())
	{
		const auto it = std::find_if(nameToDrawTypeMap.cbegin(), nameToDrawTypeMap.cend(),
			[&strategy](const auto & element) {
				return element.second == strategy;
			});
		if (it != nameToDrawTypeMap.cend())
		{
			const auto translatedName = translationService->getTranslation(drawConstToTranslationMap.at(it->first));
			drawMethodsParams.add(ofParameter<bool>(translatedName, false));
		}
	}
	
	if(drawMethodsParams.size() != 0)
	{
		drawMethodsGroup = gui.addGroup();
		drawMethodsGroup->add(drawMethodsParams);
		drawMethodsGroup->setExclusiveToggles(true);
		drawMethodsGroup->getActiveToggleIndex().addListener(this, &VisualizationModeView::onDrawTypeChanged);
		drawMethodsGroup->loadTheme(DEFAULT_THEME, true);
		drawMethodsGroup->setActiveToggle(currentDrawIndex);
		drawMethodsGroup->minimize();
	}
}

void VisualizationModeView::setupPropertiesParams()
{
	propertiesParams.setName(translationService->getTranslation(Tc::Options));
	propertiesParams.add(arraySizeParam.set(translationService->getTranslation(Tc::ArraySize), arraySize, 10, 1000));
	propertiesParams.add(firstColorParam.set(translationService->getTranslation(Tc::Color1), ofColor(0,255,0),ofColor(10,10,10), ofColor(255,255,255)));
	propertiesParams.add(secondColorParam.set(translationService->getTranslation(Tc::Color2), ofColor(0,0,255),ofColor(10,10,10), ofColor(255,255,255)));
}

void VisualizationModeView::setupPropertiesGroup()
{
	arraySizeParam.addListener(this, &VisualizationModeView::onArraySizeChanged);
	firstColorParam.addListener(this, &VisualizationModeView::onFirstColorChanged);
	secondColorParam.addListener(this, &VisualizationModeView::onSecondColorChanged);

	propertiesGroup = gui.addGroup();
	propertiesGroup->setPosition(drawMethodsGroup->getShape().getTopRight());
	propertiesGroup->add(propertiesParams);
	propertiesGroup->loadTheme(DEFAULT_THEME, true);
	propertiesGroup->minimizeAll();
	propertiesGroup->minimize();
}

void VisualizationModeView::setupSpeedControl()
{
	speedParams.add(speedParam.set(translationService->getTranslation(Tc::Speed), 0.5, 0.1, 1));
	speedParam.addListener(this, &VisualizationModeView::onSortSpeedChanged);

	speedGroup = gui.addGroup();
	speedGroup->setPosition(propertiesGroup->getShape().getTopRight());
	speedGroup->add(speedParams);
	speedGroup->setShowHeader(false);
	speedGroup->loadTheme(DEFAULT_THEME, true);
}

void VisualizationModeView::setupColors()
{
	const auto drawStrategy = drawService->getDrawStrategy();
	drawStrategy->updateFirstColor(firstColorParam.get());
	drawStrategy->updateSecondColor(secondColorParam.get());
}

void VisualizationModeView::arraySetup() const
{
	sortResetButton->setText(translationService->getTranslation(Tc::ButtonSort));

	sortService->stopSorting();
	arrayService->initializeArray(ArrayProperties(arraySize, 0), false);
	drawService->updateArray();

}

void VisualizationModeView::onArraySizeChanged(int & size)
{
	arraySize = size;
	arraySetup();
}

void VisualizationModeView::onSortSpeedChanged(float & delayRatio)
{
	sortService->updateSortingSpeed(delayRatio);
}

void VisualizationModeView::onButtonPressed(std::string & str)
{
	if(!uiHidden)
	{
		if (str == translationService->getTranslation(Tc::ButtonBack))
		{
			drawService->stopDrawing();
			sortService->stopSorting();
			viewService->addToContext(MODE_CONTEXT, mode);
			viewService->setCurrentView(ViewType::AlgorithmSelectionView);
		}
		else if (str == translationService->getTranslation(Tc::ButtonSort))
		{
			sortResetButton->setText(translationService->getTranslation(Tc::ButtonReset));
			minimizeGroups();

			sortService->stopSorting();
			sortService->sort(false);
		}
		else if (str == translationService->getTranslation(Tc::ButtonReset))
		{
			arraySetup();
		}
	}
}

void VisualizationModeView::onDrawTypeChanged(int & index)
{
	currentDrawIndex = index;
	const auto name = drawMethodsParams.get(currentDrawIndex).getName();
	const auto it = std::find_if(drawConstToTranslationMap.begin(), drawConstToTranslationMap.end(), [this, &name](const auto & element)
	{
		return translationService->getTranslation(element.second) == name;
	});
	if(it != drawConstToTranslationMap.end())
	{
		drawService->setDrawStrategy(nameToDrawTypeMap.at(it->first));
	}
	setupColors();
	minimizeGroups();
}

void VisualizationModeView::onFirstColorChanged(ofColor & color)
{
	drawService->getDrawStrategy()->updateFirstColor(color);
}

void VisualizationModeView::onSecondColorChanged(ofColor & color)
{
	drawService->getDrawStrategy()->updateSecondColor(color);
}

void VisualizationModeView::onKeyPressed(ofKeyEventArgs & ev)
{
	if (ev.key == OF_KEY_BACKSPACE)
	{
		drawService->stopDrawing();
		sortService->stopSorting();
		viewService->addToContext(MODE_CONTEXT, mode);
		viewService->setCurrentView(ViewType::AlgorithmSelectionView);
	}
	else if (ev.key == 'r')
	{
		arraySetup();
	}
	else if (ev.key == 'h')
	{
		uiHidden = !uiHidden;
		gui.getVisible().set(!uiHidden);
	}
}

void VisualizationModeView::onWindowResized(ofResizeEventArgs &)
{
	setButtonsParameters();
}

void VisualizationModeView::minimizeGroups() const
{
	if(drawMethodsGroup != nullptr)
	{
		drawMethodsGroup->minimize();
	}
	if(propertiesGroup != nullptr)
	{
		propertiesGroup->minimize();
	}
}

void VisualizationModeView::cleanup()
{
	ofRemoveListener(ofEvents().keyPressed, this, &VisualizationModeView::onKeyPressed);
	ofRemoveListener(ofEvents().windowResized, this, &VisualizationModeView::onWindowResized);

	for(const auto & button : buttons)
	{
		ofRemoveListener(button->clickedInside, this, &VisualizationModeView::onButtonPressed);
	}

	ofRemoveListener(backButton->clickedInside, this, &VisualizationModeView::onButtonPressed);

	sortService->stopSorting();
}
