#include "BFSSnake.h"
#include "PathSolver.h"
#include "../../models/Direction.h"
#include <deque>
#include "../../Game.h"
#include "../Food.h"
#include "../../util/Logging.h"

BFSSnake::~BFSSnake()
{
}

Direction::Direction BFSSnake::next_direction() {
	if (this->body.size() == 0) return Direction::NONE;

	PathSolver pathSolver = PathSolver(*this);

	Food food = *(Game::getInstance()->foods.at(0));
	Point foodPoint = Point((int) food.getLocation().x, (int) food.getLocation().y);

	std::string a(std::to_string(Game::getInstance()->getSnake()->getBody().size()));
	std::deque<Direction::Direction> path = pathSolver.shortestPathTo(foodPoint);;

	if (path.size() == 0) return chooseNextMove(Direction::UP);

	if (isNextMoveValid(path.at(0))) return path.at(0);

	return chooseNextMove(path.at(0));
}
