#pragma once
#include "AISnake.h"
#include <SFML/Graphics.hpp>

class BFSSnake : public AISnake
{
public:
	BFSSnake(sf::RenderWindow *sf, int playerIndex) : AISnake(sf, playerIndex) {
		if (this->body.size() == 0) {
			body.push_back(Utils::getRectangleAt(sf::Vector2f((float)this->x, (float)this->y), sf::Vector2f(16, 16), this->headColor));
		}
	}
	~BFSSnake();

private:
	Direction::Direction next_direction() override;
};

