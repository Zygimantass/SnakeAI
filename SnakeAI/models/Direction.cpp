#pragma once
#include "Direction.h"
#include <SFML/Graphics.hpp>

namespace Direction {

	// converts enum to vector2f, takes Enum, returns sf::Vector2f
	sf::Vector2f getVectorDir(Direction dir) {
		switch (dir) {
		case Direction::LEFT:
			return sf::Vector2f(-1, 0);
		case Direction::RIGHT:
			return sf::Vector2f(1, 0);
		case Direction::UP:
			return sf::Vector2f(0, -1);
		case Direction::DOWN:
			return sf::Vector2f(0, 1);
		case Direction::NONE:
		default:
			return sf::Vector2f(0, 0);
		}
	}
	
	// returns the opposite direction of argument dir
	Direction opposite(Direction dir) {
		switch (dir) {
		case Direction::LEFT:
			return Direction::RIGHT;
		case Direction::RIGHT:
			return Direction::LEFT;
		case Direction::UP:
			return Direction::DOWN;
		case Direction::DOWN:
			return Direction::UP;
		case Direction::NONE:
		default:
			return Direction::NONE;
		}
	}
}