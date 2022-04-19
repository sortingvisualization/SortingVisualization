#include "TranslationService.h"

#include "Logger.h"
#include "ofJson.h"

namespace 
{
std::map<Language, std::string> languageToTranslationFileMap =
{
	{Language::English, "en.json"},
	{Language::Polish, "pl.json"},
};

constexpr auto MISSING_TRANSLATION = "MissingTranslation";
}

TranslationService::TranslationService(const Language language)
{
	initialize();
	loadLanguage(language);
}

void TranslationService::loadLanguage(const Language language)
{
	currentLanguage = language;
	const auto json = ofLoadJson(languageToTranslationFileMap.at(language));

	for(const auto item : json.items())
	{
		try
		{
			translationKeyToTextMap.at(item.key()) = item.value().get<std::string>();
		}
		catch (const std::exception & ex)
		{
			logger("Missing translation in JSON file:", ex.what());
		}
	}
}

std::string TranslationService::getTranslation(const Tc key) const
{
	std::string translation = MISSING_TRANSLATION;
	const auto it = translationConstToKeyMap.find(key);

	if(it != translationConstToKeyMap.end())
	{
		translation = translationKeyToTextMap.at(it->second);
	}

	return translation;
}

Language TranslationService::getNextLanguage() const
{
	auto it = languageToTranslationFileMap.find(currentLanguage);
	if(it != languageToTranslationFileMap.end())
	{
		if(it++ != languageToTranslationFileMap.end())
		{
			return it->first;
		}

		return languageToTranslationFileMap.begin()->first;
	}

	return currentLanguage;
}

void TranslationService::initialize()
{
	for(const auto & element : translationConstToKeyMap)
	{
		translationKeyToTextMap.emplace(element.second, element.second);
	}
}
