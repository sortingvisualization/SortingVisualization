#pragma once
#include <string>

namespace
{
void stringSubstitute(std::string & str, const std::string & from, const std::string & to)
{
	std::string tempStr;
	tempStr.reserve(str.length());

	std::string::size_type currentPos = 0;
	const auto it = str.find(from, currentPos);

	if (it != std::string::npos)
	{
		tempStr.append(str, currentPos, it - currentPos);
		tempStr += to;
		currentPos = it + from.length();
	}

	tempStr += str.substr(currentPos);

	str.swap(tempStr);
}
}
