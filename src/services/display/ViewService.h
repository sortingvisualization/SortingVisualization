#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ViewDefinitions.h"

class IView;
class ViewFactory;

class ViewService
{
public:
	ViewService() = default;

	std::shared_ptr<IView> getCurrentView() const;
	void setCurrentView(ViewType);

	void addToContext(const std::string & key, const std::string & value);
	bool keyExists(const std::string & key) const;
	std::string getValue(const std::string & key) const;
	void clearContext();

	void setViewFactory(std::shared_ptr<ViewFactory>);

private:
	std::shared_ptr<ViewFactory> viewFactory;

	std::shared_ptr<IView> currentView;
	std::map<std::string, std::string> context;
};

