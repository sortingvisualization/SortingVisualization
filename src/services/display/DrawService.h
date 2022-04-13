#pragma once
#include <memory>
#include <vector>

#include "DrawDefinitions.h"

class ArrayModel;
class ArrayService;
class DrawFactory;
class IDrawStrategy;
class IView;
class ViewService;

class DrawService
{
public:
	explicit DrawService(std::shared_ptr<ArrayService>, std::shared_ptr<ViewService>, std::shared_ptr<DrawFactory> );

	void draw() const;
	void setDrawStrategy(DrawType);
	void stopDrawing();
	std::shared_ptr<IDrawStrategy> getDrawStrategy() const;
	std::vector<DrawType> getDrawTypes() const;
	void updateArray();

private:
	std::shared_ptr<ArrayService> arrayService;
	std::shared_ptr<ViewService> viewService;
	std::shared_ptr<DrawFactory> drawFactory;

	std::vector<DrawType> drawTypes;
	std::shared_ptr<IDrawStrategy> drawStrategy;
	std::shared_ptr<ArrayModel> currentArray;
};
