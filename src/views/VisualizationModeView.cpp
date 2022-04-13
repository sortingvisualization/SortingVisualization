#include "VisualizationModeView.h"

#include "ArrayModel.h"
#include "ArrayService.h"
#include "DrawService.h"
#include "GuiConsts.h"
#include "IDrawStrategy.h"
#include "Logger.h"
#include "SortDefinitions.h"
#include "SortService.h"
#include "ViewService.h"

VisualizationModeView::VisualizationModeView(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<DrawService> drawService, 
	std::shared_ptr<SortService> sortService, std::shared_ptr<ViewService> viewService)
	: arrayService(std::move(arrayService))
	, drawService(std::move(drawService))
	, sortService(std::move(sortService))
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

	drawService->setDrawStrategy(DrawType::ColumnsDraw);

	setupColors();
	arraySetup();
}

void VisualizationModeView::setupButtons()
{
	setupBackButton();
	setupSortButton();
	setupResetButton();
	setupDrawMethodsGroup();
	setupPropertiesParams();
	setupPropertiesGroup();
	setupSpeedControl();
}

void VisualizationModeView::setupBackButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(BACK_BUTTON_LABEL);
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &VisualizationModeView::onButtonPressed);
}

void VisualizationModeView::setupSortButton()
{
	backButton = std::make_shared<Button>(0, 0, 0, 0);
	backButton->setText(BACK_BUTTON_LABEL);
	backButton->setBackgroundColor(ofColor(227, 64, 27));

	ofAddListener(backButton->clickedInside, this, &VisualizationModeView::onButtonPressed);
}

void VisualizationModeView::setupResetButton()
{
	sortResetButton = std::make_shared<Button>(0, 0, 0, 0);
	sortResetButton->setText(SORT_BUTTON_LABEL);
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
	drawMethodsParams.setName(DRAW_METHOD_GROUP);
	for (const auto & strategy : drawService->getDrawTypes())
	{
		const auto it = std::find_if(nameToDrawTypeMap.cbegin(), nameToDrawTypeMap.cend(),
			[&strategy](const auto & element) {
				return element.second == strategy;
			});
		if (it != nameToDrawTypeMap.cend())
		{
			drawMethodsParams.add(ofParameter<bool>(it->first, false));
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
	propertiesParams.setName(PROPERTIES_GROUP);
	propertiesParams.add(arraySizeParam.set(ARRAY_SIZE, arraySize, 10, 1000));
	propertiesParams.add(firstColorParam.set(COLOR_1, ofColor(0,255,0),ofColor(10,10,10), ofColor(255,255,255)));
	propertiesParams.add(secondColorParam.set(COLOR_2, ofColor(0,0,255),ofColor(10,10,10), ofColor(255,255,255)));
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
	speedParams.add(speedParam.set(SPEED, 0.5, 0.1, 1));
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
	sortResetButton->setText(SORT_BUTTON_LABEL);

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
		if (str == BACK_BUTTON_LABEL)
		{
			drawService->stopDrawing();
			sortService->stopSorting();
			viewService->addToContext(MODE_CONTEXT, mode);
			viewService->setCurrentView(ViewType::AlgorithmSelectionView);
		}
		else if (str == SORT_BUTTON_LABEL)
		{
			sortResetButton->setText(RESET_BUTTON_LABEL);
			minimizeGroups();

			sortService->stopSorting();
			sortService->sort(false);
		}
		else if (str == RESET_BUTTON_LABEL)
		{
			arraySetup();
		}
	}
}

void VisualizationModeView::onDrawTypeChanged(int & index)
{
	currentDrawIndex = index;
	const auto name = drawMethodsParams.get(currentDrawIndex).getName();
	drawService->setDrawStrategy(nameToDrawTypeMap.at(name));
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
