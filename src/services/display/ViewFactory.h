#pragma once
#include <map>
#include <functional>
#include <memory>

#include "ViewDefinitions.h"

class ArrayService;
class DrawService;
class IView;
class SortService;
class StateManager;
class ViewService;

using View = std::function<std::shared_ptr<IView>()>;

class ViewFactory
{
public:
	ViewFactory(std::shared_ptr<ArrayService>, std::shared_ptr<DrawService>, std::shared_ptr<SortService>,
		std::shared_ptr<ViewService>, std::shared_ptr<StateManager>);
	std::shared_ptr<IView> createView(ViewType) const;

private:
	void fillViewMap();

	std::shared_ptr<ArrayService> arrayService;
	std::shared_ptr<DrawService> drawService;
	std::shared_ptr<SortService> sortService;
	std::shared_ptr<ViewService> viewService;
	std::shared_ptr<StateManager> stateManager;

	std::map<ViewType, View> viewToFunctorMap;
};
