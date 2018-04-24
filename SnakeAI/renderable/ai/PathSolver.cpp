#include "PathSolver.h"
#include <vector>
#include <algorithm>
#include "../../util/Logging.h"
#include "../../Game.h"

std::deque<Direction::Direction> PathSolver::shortestPathTo(Point dest) {
	resetTable();

	std::deque<Point> queue = std::deque<Point>();
	
	Point headPoint;

	headPoint.pos = (sf::Vector2<int>) (this->snake->getBody().at(0).getPosition());
	getCellAt(headPoint.pos.x, headPoint.pos.y, Snake::SIZE)->dist = 0;

	queue.push_back(headPoint);

	while (queue.size() != 0) {
		Point cur = queue.at(0);
		queue.pop_front();

		if (cur == dest) return build_path(headPoint, dest);

		Direction::Direction first_direction;

		if (cur == headPoint) {
			first_direction = this->snake->getLastDir();
		}
		else {
			first_direction = getCellAt(cur.pos.x, cur.pos.y, Snake::SIZE)->parent.getDirectionTo(cur);
		}

		std::vector<Point> adjs = cur.adjacentPoints();
		std::random_shuffle(adjs.begin(), adjs.end());

		for (int i = 0; i < adjs.size(); i++) {
			if (first_direction == cur.getDirectionTo(adjs[i])) {
				std::swap(adjs[0], adjs[i]);
				break;
			}
		}

		for (int i = 0; i < adjs.size(); i++) { 
			Point pos = adjs[i];

			if (Game::getInstance()->isSafe(pos)) {
				Cell* adjCell = getCellAt(pos.pos.x, pos.pos.y, Snake::SIZE);
				if (adjCell->visited ) continue;
				
				if (adjCell->dist == INT_MAX) {
					adjCell->parent = cur;
					adjCell->dist = getCellAt(cur.pos.x, cur.pos.y, Snake::SIZE)->dist + 1;
					queue.push_back(pos);
				}
			}
		}

	}
	return std::deque<Direction::Direction>();
}

std::deque<Direction::Direction> PathSolver::build_path(Point src, Point dest) {
	std::deque<Direction::Direction> path;
	Point tmp = dest;

	while (tmp != src) {
		Point parent = cell_table.at(tmp.pos.x / Snake::SIZE).at(tmp.pos.y / Snake::SIZE).parent;
		Direction::Direction dir = parent.getDirectionTo(tmp);
		path.push_back(dir);
		tmp = parent;
	}

	return path;
}