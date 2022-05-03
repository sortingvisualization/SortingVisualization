#pragma once
#include <iostream>

namespace
{
template <class T> static void logger(T message)
{
	std::cout << message << std::endl;
}

template <class T, class... Args> static void logger(T message, Args ... args)
{
	std::cout << message << " ";
	logger(args...);
}
}
