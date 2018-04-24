#pragma once
#include <SFML/Graphics.hpp>

// Enumerating directions for easier use

namespace Direction {
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	// converts enum to vector2f, takes Enum, returns sf::Vector2f
	sf::Vector2f getVectorDir(Direction dir);

	// returns the opposite direction of argument dir
	Direction opposite(Direction dir);
}

