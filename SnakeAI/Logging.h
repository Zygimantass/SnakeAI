#pragma once
#include "Logging.h"
#include "Constants.h"
#include <string>
#include <iostream>

namespace logger {
	static const char TAG[] = "SnakeAI";

	template <typename T>
	void print(T const & msg)
	{
#ifndef NDEBUG
		std::cout << "[" << logger::TAG << "] " << msg << std::endl;
#endif
		return;
	}
}