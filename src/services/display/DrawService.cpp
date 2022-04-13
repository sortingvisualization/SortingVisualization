#include "DrawService.h"
#include "ArrayModel.h"
#include "ArrayService.h"
#include "DrawFactory.h"
#include "ViewService.h"
#include "IView.h"
#include "Logger.h"


DrawService::DrawService(std::shared_ptr<ArrayService> arrayService, std::shared_ptr<ViewService> viewService,
	std::shared_ptr<DrawFactory> drawFactory)
	: arrayService(std::move(arrayService))
	, viewService(std::move(viewService))
	, drawFactory(std::move(drawFactory))
{
	drawTypes = {
		{DrawType::CircleDraw},
		{DrawType::ColumnsDraw},
		{DrawType::LinesDraw},
		{DrawType::PyramidDraw},
	};
}

void DrawService::draw() const
{
	const auto currentView = viewService->getCurrentView();
	if (drawStrategy != nullptr)
	{
		drawStrategy->draw(currentArray->getArray());
	}
	if (currentView != nullptr)
	{
		currentView->draw();
	}
}

void DrawService::setDrawStrategy(const DrawType strategy)
{
	drawStrategy = drawFactory->createDrawStrategy(strategy);
}

void DrawService::stopDrawing()
{
	drawStrategy.reset();
}

std::shared_ptr<IDrawStrategy> DrawService::getDrawStrategy() const
{
	return drawStrategy;
}

std::vector<DrawType> DrawService::getDrawTypes() const
{
	return drawTypes;
}

void DrawService::updateArray()
{
	currentArray = arrayService->getArrayModel();
}
