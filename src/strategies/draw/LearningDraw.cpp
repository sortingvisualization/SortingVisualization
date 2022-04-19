#include "LearningDraw.h"
#include "DrawDefinitions.h"
#include "DrawHelpers.h"
#include "ofAppRunner.h"
#include "StateManager.h"
#include "StringSubstitute.h"
#include "TranslationService.h"

namespace
{
std::map<ElementState, ofColor> markerToColorMap = 
{
	{ElementState::Unsorted, ofColor(51, 153, 255)},
	{ElementState::Sorted, ofColor(102, 204, 0)},
	{ElementState::Selected, ofColor(255, 0, 0)},
	{ElementState::Compared, ofColor(0, 0, 255)},
	{ElementState::MergeLeftPart, ofColor(255, 128, 0)},
	{ElementState::MergeRightPart, ofColor(127, 0, 255)},
	{ElementState::PivotLeft, ofColor(255, 128, 0)},
	{ElementState::PivotRight, ofColor(127, 0, 255)},
	{ElementState::Bucket, ofColor(115, 115, 225)},
	{ElementState::BucketSum, ofColor(255, 128, 0)},
	{ElementState::Hidden, ofColor(0, 0, 0, 0)},
};

template<class It>
int getMaxElementValue(It first, It last)
{
	std::vector<ArrayElement> tempArray;
	for (auto it = first; it != last; ++it)
	{
		tempArray.insert(tempArray.end(), it->begin(), it->end());
	}

	const auto maxIt = std::max_element(tempArray.begin(), tempArray.end(), 
        [](const auto & a, const auto & b){return a.value < b.value;});

	if(maxIt != tempArray.end())
	{
		return maxIt->value;
	}

	return 0;
}
}

LearningDraw::LearningDraw(std::shared_ptr<TranslationService> translationService, std::shared_ptr<StateManager> stateManager)
	: translationService(std::move(translationService))
	, stateManager(std::move(stateManager))
{
	reloadFont();
	ofAddListener(ofEvents().keyPressed, this, &LearningDraw::onKeyPressed);
	ofAddListener(ofEvents().windowResized, this, &LearningDraw::onWindowResized);
}

LearningDraw::~LearningDraw()
{
	ofRemoveListener(ofEvents().keyPressed, this, &LearningDraw::onKeyPressed);
	ofRemoveListener(ofEvents().windowResized, this, &LearningDraw::onWindowResized);
}

void LearningDraw::draw(const std::vector<ArrayElement> &)
{
	if(stateManager->hasStates())
	{
		const auto currentState = stateManager->getCurrentState();
		const auto arrays = currentState.getArrays();

		const auto size = arrays.size();
		const auto maxValue = getMaxElementValue(arrays.begin(), arrays.end());

		for(int i = size; i > 0; --i)
		{
			if(stateManager->getSortType() == SortType::RadixSort)
			{
				drawBuckets(arrays.at(i - 1), size, i);
			}
			else
			{
				drawColumns(arrays.at(i - 1), size, maxValue, i);
			}
		}
	}
}

void LearningDraw::drawColumns(const std::vector<ArrayElement>& array, const int arraysCount, const int maxValue, const int position) const
{
	const double drawSurfaceWidth = ofGetWindowWidth();
	const double drawSurfaceHeight = ofGetWindowHeight() * 0.9;

	for(int i = 0; i < array.size(); ++i)
	{
		const auto columnWidth = drawSurfaceWidth * 0.9 / MAX_ELEMENTS_LEARNING_MODE;
		const auto columnHeight = (drawSurfaceHeight / 2 / maxValue * array.at(i).value) * 0.7;
		const auto offsetX = drawSurfaceWidth * 0.5 - array.size() * ((columnWidth + COLUMN_PADDING) * 0.5);

		const auto columnPosX = (columnWidth + COLUMN_PADDING) * i + offsetX;
		auto columnPosY = drawSurfaceHeight / arraysCount * position - drawSurfaceHeight * 0.1 * position;
		if(arraysCount == 1)
		{
			columnPosY *= 0.75;
		}

		ofSetColor(markerToColorMap.at(array.at(i).elementState));
		ofDrawRectangle(columnPosX, columnPosY, columnWidth, -columnHeight);

		if(array.at(i).elementState != ElementState::Hidden)
		{
			const auto columnValuePosX = columnPosX + columnWidth / 2;
			const auto columnValuePosY = columnPosY + 20;

			drawCenteredText(std::to_string(array.at(i).value), columnValuePosX, columnValuePosY, ofColor(25, 25, 25), basicFont);
		}
	}

	drawStateContext();
}

void LearningDraw::drawBuckets(const std::vector<ArrayElement> & array, const int arraysCount, const int position) const
{
	const double drawSurfaceWidth = ofGetWindowWidth();
	const double drawSurfaceHeight = ofGetWindowHeight() * 0.8;

	for(int i = 0; i < array.size(); ++i)
	{
		const auto bucketWidth = drawSurfaceWidth * 0.95 / MAX_ELEMENTS_LEARNING_MODE;
		const auto bucketHeight = drawSurfaceHeight * 0.1;
		const auto offsetX = drawSurfaceWidth * 0.5 - array.size() * ((bucketWidth + COLUMN_PADDING) * 0.5);

		const auto bucketPosX = (bucketWidth + COLUMN_PADDING) * i + offsetX;
		const auto bucketPosY = drawSurfaceHeight / arraysCount * position * 0.9;

		ofSetColor(markerToColorMap.at(array.at(i).elementState));
		ofDrawRectangle(bucketPosX, bucketPosY, bucketWidth, - bucketHeight);

		if(array.at(i).elementState != ElementState::Hidden)
		{
			const auto bucketValuePosX = bucketPosX + bucketHeight / 2;
			const auto bucketValuePosY = bucketPosY - bucketHeight / 2;

			if(array.at(i).value != 0 || position != 3)
			{
				drawCenteredText(std::to_string(array.at(i).value), bucketValuePosX, bucketValuePosY, ofColor(225, 225, 225), basicFont);
			}

			if(position > 1)
			{
				const auto bucketLabelPosX = bucketPosX + bucketHeight / 2;
				const auto bucketLabelPosY = bucketPosY + 20;
				const std::string bucketLabel = "[" + std::to_string(i) + "]";
				drawCenteredText(bucketLabel, bucketLabelPosX, bucketLabelPosY, ofColor(25, 25, 25), basicFont);
			}
		}
	}

	drawStateContext();
}

void LearningDraw::drawStateContext() const
{
	if(!uiHidden)
	{
		const double drawSurfaceWidth = ofGetWindowWidth();
		const double drawSurfaceHeight = ofGetWindowHeight();

		const auto boxPositionX = drawSurfaceWidth * 0.65;
		const auto boxPositionY = drawSurfaceHeight * 0.85;

		const auto boxWidth = drawSurfaceWidth * 0.35;
		const auto boxHeight = drawSurfaceHeight * 0.15;

		ofSetColor(ofColor(102, 178, 255));
		ofDrawRectangle(boxPositionX, boxPositionY, boxWidth, boxHeight);

		const auto stateContext = stateManager->getStateContext();
		std::string contextText; 

		if(stateContext.state != SortState::NoContext)
		{
			contextText = addValuesToContext(stateContext);
		}

		drawCenteredText(contextText, boxPositionX + boxWidth / 2, boxPositionY + boxHeight / 2, ofColor(255, 255, 255), contextFont);
	}
}

void LearningDraw::drawCenteredText(const std::string & text, const double posX, const double posY, const ofColor color, ofTrueTypeFont font) const
{
	const auto bounds = font.getStringBoundingBox(text, 0, 0);
	const auto offset = ofVec2f( std::floor(-bounds.x - bounds.width * 0.5), std::floor(-bounds.y - bounds.height * 0.5) );

	ofSetColor(color);
	font.drawString(text, posX + offset.x, posY + offset.y);
}

std::string LearningDraw::addValuesToContext(const StateContext & stateContext) const
{
	std::string result;

	const auto it = sortStateToTranslationMap.find(stateContext.state);
	if(it != sortStateToTranslationMap.end())
	{
		result = translationService->getTranslation(it->second);
		auto values = stateContext.values;

		while(!values.empty())
		{
			stringSubstitute(result, VALUE_PLACEHOLDER, std::to_string(values.front()));
			values.pop_front();
		}
	}

	return result;
}

void LearningDraw::onKeyPressed(ofKeyEventArgs & ev)
{
	if (ev.key == 'h')
	{
		uiHidden = !uiHidden;
	}
}

void LearningDraw::onWindowResized(ofResizeEventArgs &)
{
	reloadFont();
}

void LearningDraw::reloadFont()
{
	basicFontSize = (ofGetWindowWidth() / 75 + ofGetScreenHeight() / 75) / 2;
	ofTrueTypeFontSettings basicFontSettings("mono.ttf", basicFontSize);
	basicFontSettings.addRange(ofUnicode::Latin);
	basicFontSettings.addRange(ofUnicode::LatinA);

	basicFont.load(basicFontSettings);

	contextFontSize = (ofGetWindowWidth() / 85 + ofGetScreenHeight() / 85) / 2;
	ofTrueTypeFontSettings contextFontSettings("mono.ttf", contextFontSize);
	contextFontSettings.addRange(ofUnicode::Latin);
	contextFontSettings.addRange(ofUnicode::LatinA);
	contextFontSettings.addRange(ofUnicode::Latin1Supplement);

	contextFont.load(contextFontSettings);
}
