#pragma once
#include <climits>
#include <vector>
#include "../../util/Constants.h"
#include "../../renderable/Food.h"
#include "../../models/Point.cpp"
#include "../Snake.h"
#include <deque>

// Struct Cell for population in cell_table
struct Cell {
	Cell() {

	}

	int dist = INT_MAX;
	bool visited = false;
	Point parent;

	void reset() {
		this->dist = INT_MAX;
		this->visited = false;
		parent = Point();
	}
};

// PathSolver class, solves the shortest path based on BFS algorithm
class PathSolver
{
public:
	//ctor
	PathSolver() {

	}
	//ctor, takes Snake pointer
	PathSolver(Snake &snake) {
		this->snake = &snake;

		// populating the cell_table with default Cells

		int gridX = Constants::SCREEN_WIDTH / Food::SIZE;
		int gridY = Constants::SCREEN_HEIGHT / Food::SIZE;

		for (int i = 0; i < gridX; i++) {
			std::vector<Cell> tmpVector;
			
			for (int j = 0; j < gridY; j++) {
				Cell c;
				c.reset();

				tmpVector.push_back(c);
			}

			cell_table.push_back(tmpVector);
		}
	}
	~PathSolver() {

	}

	// takes a destination, returns a deque of directions (the shortest path)
	std::deque<Direction::Direction> shortestPathTo(Point dest);
private:
	// helper function for getting a cell, takes x, y, size, returns a pointer to the Cell

	Cell* getCellAt(int x, int y, int size) {
		int cellX = (x / size);
		int cellY = (y / size);

		return &(cell_table.at(cellX).at(cellY));
	}

	Snake* snake;
	std::vector<std::vector<Cell>> cell_table;

	// takes src, des, returns a built path
	std::deque<Direction::Direction> build_path(Point src, Point des);


	// resets and repopulates the cell_table
	void resetTable() {
		cell_table.clear();

		int gridX = Constants::SCREEN_WIDTH / Food::SIZE;
		int gridY = Constants::SCREEN_HEIGHT / Food::SIZE;

		for (int i = 0; i < gridX; i++) {
			std::vector<Cell> tmpVector;

			for (int j = 0; j < gridY; j++) {
				Cell c;
				c.reset();

				tmpVector.push_back(c);
			}

			cell_table.push_back(tmpVector);
		}
	}
};

