#pragma once

// header guard
#ifndef POINT_CPP
#define POINT_CPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Direction.h"
#include "../util/Logging.h"

// struct for a Point for easier use
struct Point {

	// default ctor
	Point() {

	}

	// ctor, that takes Vector2<int> for position
	Point(sf::Vector2<int> pos) {
		this->pos = pos;
	}

	// Point position
	sf::Vector2<int> pos;

	// ctor, that takes x and y for position
	Point(int x, int y) {
		pos = sf::Vector2<int>(x, y);
	}
	
	// overloading operators

	bool operator==(const Point &other) const {
		return (pos.x == other.pos.x && pos.y == other.pos.y);
	}

	bool operator!=(const Point &other) const {
		return !(pos.x == other.pos.x && pos.y == other.pos.y);
	}

	// get direction to other point

	Direction::Direction getDirectionTo(Point other) {
		if (pos.x == other.pos.x) {
			int diff = pos.y - other.pos.y;

			if (diff == 16) {
				return Direction::UP;
			}
			else if (diff == -16) {
				return Direction::DOWN;
			}
		}
		else if (pos.y == other.pos.y) {
			int diff = pos.x - other.pos.x;

			if (diff == 16) {
				return Direction::LEFT;
			}
			else if (diff == -16) {
				return Direction::RIGHT;
			}
		}

		return Direction::NONE;
	}

	// takes argument dir and returns Point that's adjacent to this point

	Point adjacentPoint(Direction::Direction dir) {
		switch (dir) {
		case Direction::LEFT:
			return Point(pos.x - 16, pos.y);
		case Direction::RIGHT:
			return Point(pos.x + 16, pos.y);
		case Direction::UP:
			return Point(pos.x, pos.y - 16);
		case Direction::DOWN:
			return Point(pos.x, pos.y + 16);
		default:
			return Point(pos.x, pos.y);
		}
	}

	// returns a vector of adjacent points

	std::vector<Point> adjacentPoints() {
		std::vector<Point> adjPoints;

		adjPoints.push_back(adjacentPoint(Direction::RIGHT));
		adjPoints.push_back(adjacentPoint(Direction::LEFT));
		adjPoints.push_back(adjacentPoint(Direction::DOWN));
		adjPoints.push_back(adjacentPoint(Direction::UP));

		return adjPoints;
	}
};

#endif