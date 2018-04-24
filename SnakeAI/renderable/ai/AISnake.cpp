#include "AISnake.h"
#include "../../Game.h"

AISnake::~AISnake()
{
}

void AISnake::update(float dt) {
	// moving every 1.0 / speed seconds, checking for eaten food and moving based on this->next_direction()

	if (secondsSinceLastMove > (1.0 / speed)) {

		int eatenFood = this->ateFood();

		if (eatenFood != -1) {
			Game::getInstance()->foods.erase(Game::getInstance()->foods.begin() + eatenFood);
			Game::getInstance()->addFood(1);
			this->addScore();
			this->speed += 1;
		}

		this->lastDir = this->next_direction();

		this->move(this->lastDir);
		this->secondsSinceLastMove = 0;
	}
	else {
		this->secondsSinceLastMove += dt;
	}
}

Direction::Direction AISnake::next_direction() {
	return Direction::NONE;
}