#pragma once
#include <map>
#include <string>

#include "TranslationConsts.h"

enum class Language
{
	English,
	Polish
};

class TranslationService
{
public:
	explicit TranslationService(Language);

	void loadLanguage(Language);
	std::string getTranslation(Tc key) const;
	Language getNextLanguage() const;

private:
	void initialize();
	std::map<std::string, std::string> translationKeyToTextMap;

	Language currentLanguage;
};
