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

	// creating a PathSolver

	PathSolver pathSolver = PathSolver(*this);

	// getting destination (food)

	Food food = *(Game::getInstance()->foods.at(0));
	Point foodPoint = Point((int) food.getLocation().x, (int) food.getLocation().y);

	// geting path from PathSolver

	std::deque<Direction::Direction> path = pathSolver.shortestPathTo(foodPoint);;

	// if path is invalid we try to find a valid solution

	if (path.size() == 0) return chooseNextMove(Direction::UP);

	if (isNextMoveValid(path.at(0))) return path.at(0);

	// choosing a valid direction

	Direction::Direction dir = chooseNextMove(path.at(0));

	return dir;
}
