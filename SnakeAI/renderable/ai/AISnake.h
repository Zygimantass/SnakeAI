#pragma once
#include <list>
#include <array>
#include "../../util/Constants.h"
#include "../../util/Logging.h"
#include "../../util/Utils.h"
#include ".././Snake.h"
#include "../../models/Direction.h"

// Class for AI snake, inherits Snake which inherits Renderable

class AISnake : public Snake
{
public:

	// ctor
	AISnake(sf::RenderWindow *sf, int playerIndex) : Snake(sf, playerIndex) {

	};
	~AISnake();

	// overriding update function for our own use
	void update(float dt) override;
protected:
	// takes a nextMove and returns a boolean depending on if it's valid
	bool isNextMoveValid(Direction::Direction nextMove) {
		// gets head pos
		int headX = (int) this->body[0].getPosition().x;
		int headY = (int) this->body[0].getPosition().y;

		// moves head based on direction nextMove
		sf::Vector2f dir = Direction::getVectorDir(nextMove);
		headX += (int) dir.x * 16;
		headY += (int) dir.y * 16;

		// validates move
		
		if (headX < 0 || headY < 0 || headX >= Constants::SCREEN_WIDTH || headY >= Constants::SCREEN_HEIGHT) {
			return false;
		}

		// validates move depending on collision with itself

		if (this->body.size() > 1) {
			sf::Vector2f body((float) headX, (float) headY);

			if (this->collidesBody(body)) {
				return false;
			}
		}

		return true;
	}

	// chooses next valid move, if the one that we give the function (currDir) is invalid
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

	// function that needs implementation in inherited classes. returns next direction
	virtual Direction::Direction next_direction();
};

