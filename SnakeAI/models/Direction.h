#pragma once
#include <SFML/Graphics.hpp>

namespace Direction {
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	sf::Vector2f getVectorDir(Direction dir);
	Direction opposite(Direction dir);
}

