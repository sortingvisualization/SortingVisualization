#pragma once
#include "BaseDraw.h"
#include "ofTrueTypeFont.h"

class StateManager;
class TranslationService;

class LearningDraw : public BaseDraw
{
public:
	LearningDraw(std::shared_ptr<TranslationService>, std::shared_ptr<StateManager>);
	~LearningDraw();

	void draw(const std::vector<ArrayElement> &) override;

private:
	void drawColumns(const std::vector<ArrayElement> &, int arraysCount, int maxValue, int position) const;
	void drawBuckets(const std::vector<ArrayElement> &, int arraysCount, int position) const;
	void drawStateContext() const;
	void drawCenteredText(const std::string & text, double posX, double posY, ofColor, ofTrueTypeFont) const;

	std::string addValuesToContext(const StateContext & stateContext) const;

	void reloadFont();

	void onKeyPressed(ofKeyEventArgs &);
	void onWindowResized(ofResizeEventArgs &);

	std::shared_ptr<TranslationService> translationService;
	std::shared_ptr<StateManager> stateManager;

	bool uiHidden{false};

	ofTrueTypeFont basicFont;
	int basicFontSize{0};
	ofTrueTypeFont contextFont;
	int contextFontSize{0};
};
