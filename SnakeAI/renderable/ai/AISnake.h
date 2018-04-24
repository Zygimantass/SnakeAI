#pragma once
#include <list>
#include <array>
#include "../../util/Constants.h"
#include "../../util/Logging.h"
#include "../../util/Utils.h"

#include ".././Snake.h"

#include "../../models/Direction.h"

class AISnake : public Snake
{
public:
	AISnake(sf::RenderWindow *sf, int playerIndex) : Snake(sf, playerIndex) {

	};
	~AISnake();

	void update(float dt) override;
protected:
	bool isNextMoveValid(Direction::Direction nextMove) {
		int headX = (int) this->body[0].getPosition().x;
		int headY = (int) this->body[0].getPosition().y;

		sf::Vector2f dir = Direction::getVectorDir(nextMove);
		headX += (int) dir.x * 16;
		headY += (int) dir.y * 16;

		if (headX < 0 || headY < 0 || headX >= Constants::SCREEN_WIDTH || headY >= Constants::SCREEN_HEIGHT) {
			return false;
		}

		if (this->body.size() > 1) {
			sf::Vector2f body((float) headX, (float) headY);

			if (this->collidesBody(body)) {
				return false;
			}
		}

		return true;
	}

	Direction::Direction chooseNextMove(Direction::Direction currDir) {
		if (isNextMoveValid(Direction::UP) && currDir != Direction::UP) {
			return Direction::UP;
		}
		else if (isNextMoveValid(Direction::DOWN) && currDir != Direction::DOWN) {
			return Direction::DOWN;
		}
		else if (isNextMoveValid(Direction::LEFT) && currDir != Direction::LEFT) {
			return Direction::LEFT;
		}
		else if (isNextMoveValid(Direction::RIGHT) && currDir != Direction::RIGHT) {
			return Direction::RIGHT;
		}

		return Direction::NONE;
	}
	virtual Direction::Direction next_direction();
};

