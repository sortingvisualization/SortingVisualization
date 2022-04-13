#include <algorithm>

#include "ViewService.h"
#include "IView.h"
#include "Logger.h"
#include "ViewFactory.h"

std::shared_ptr<IView> ViewService::getCurrentView() const
{
	return currentView;
}

void ViewService::setViewFactory(std::shared_ptr<ViewFactory> factory)
{
	viewFactory = std::move(factory);
	setCurrentView(ViewType::ModeSelectionView);
}

void ViewService::setCurrentView(const ViewType viewType)
{
	currentView = viewFactory->createView(viewType);
}

void ViewService::addToContext(const std::string & key, const std::string & value)
{
	context[key] = value;
}

bool ViewService::keyExists(const std::string& key) const
{
	const auto it = context.find(key);
	return it != context.end();
}

std::string ViewService::getValue(const std::string & key) const
{
	const auto it = context.find(key);
	if (it == context.end())
	{
		throw std::range_error("Key not found");
	}

	return it->second;
}

void ViewService::clearContext()
{
	context.clear();
}
