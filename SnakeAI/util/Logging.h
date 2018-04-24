#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Logging.h"
#include "Constants.h"

// logging for debugging
namespace logger {
	static const char TAG[] = "SnakeAI";

	inline
	void printCoords(sf::Vector2f vec) {
#ifndef NDEBUG
		std::cout << "[" << logger::TAG << " vec2f] (" << vec.x << " " << vec.y << ");" << std::endl;
#endif // !NDEBUG
	};

	inline
	void printCoords(sf::Vector2i vec) {
#ifndef NDEBUG
		std::cout << "[" << logger::TAG << " vec2i] (" << vec.x << " " << vec.y << ");" << std::endl;
#endif // !NDEBUG
	}

	template <typename T>
	void print(T const & msg)
	{
#ifndef NDEBUG
		std::cout << "[" << logger::TAG << "] " << msg << std::endl;
#endif
		return;
	};
}