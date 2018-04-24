#pragma once
#include "AISnake.h"
#include <SFML/Graphics.hpp>

// BFSSnake, is an AI Snake, which uses the Breadth First Search algorithm, inherits AISnake

class BFSSnake : public AISnake
{
public:
	// ctor
	BFSSnake(sf::RenderWindow *sf, int playerIndex) : AISnake(sf, playerIndex) {
		// if body for some reason is empty, we populate it with head

		if (this->body.size() == 0) {
			body.push_back(Utils::getRectangleAt(sf::Vector2f((float)this->x, (float)this->y), sf::Vector2f(16, 16), this->headColor));
		}
	}
	~BFSSnake();

private:
	// overriding next_direction() for our use
	Direction::Direction next_direction() override;
};

