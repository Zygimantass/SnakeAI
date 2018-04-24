#pragma once
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <array>
#include "../util/Constants.h"
#include "../util/Utils.h"
#include "../util/Logging.h"
#include "../models/Direction.h"
#include <sstream>

class Snake: public Renderable
{
public:
	static const int SIZE = 16;

	Snake(sf::RenderWindow *sf, int playerIndex) : Renderable(sf) {
		this->sf = sf;

		if (playerIndex == 0) {
			this->bodyColor = sf::Color::Green;
			this->headColor = sf::Color::Yellow;
		} else {
			this->bodyColor = sf::Color::Red;
			this->headColor = sf::Color::Blue;
		}

		
		this->snake_length = 1;

		this->speed = 10;

		int maxX = (Constants::SCREEN_WIDTH - Snake::SIZE) / Snake::SIZE;
		int maxY = (Constants::SCREEN_HEIGHT - Snake::SIZE) / Snake::SIZE;
		int gridX = Utils::getRandomInt(0, maxX / 2);
		int gridY = Utils::getRandomInt(0, maxY / 2);

		logger::printCoords(sf::Vector2i(gridX, gridY));
		logger::printCoords(sf::Vector2i(gridX * Snake::SIZE, gridY * Snake::SIZE));

		this->x = gridX * Snake::SIZE;
		this->y = gridY * Snake::SIZE;
		
		this->width = Snake::SIZE;
		this->height = Snake::SIZE;

		this->lastDir = Direction::Direction::DOWN;

		snakeDirections.push_back(Direction::Direction::DOWN);
		body.push_back(Utils::getRectangleAt(sf::Vector2f((float) this->x, (float) this->y), sf::Vector2f(16, 16), this->headColor));
		
		logger::printCoords(body.at(0).getPosition());

		this->playerIndex = playerIndex;
		this->currentScheme = this->controlSchemes[playerIndex];
	};

	~Snake();

	// debugging
	friend std::ostream& operator<<(std::ostream& os, const Snake& snake) {
		os << "[Snake] loc: (" << snake.x << ", " << snake.y << ")" << ", length: " << snake.snake_length;
		return os;
	}
	std::ostringstream printBody();

	// body
	std::vector<sf::RectangleShape> getBody() {
		return this->body;
	}

	Direction::Direction getLastDir() {
		return lastDir;
	}


	// display, update
	void display() override;
	void update(float dt) override;
	
	// movement
	void switchDirection(Direction::Direction dir);
	virtual void move(Direction::Direction direction);

	// death check
	bool died();

	// collision
	bool collidesHead(sf::Vector2f pos);
	bool collidesBody(sf::Vector2f pos);
	bool collides(sf::Vector2f pos);

	int getScore();
	void addScore();
	void addScore(int score);

protected:
	int ateFood();
	sf::Color headColor;
	sf::Color bodyColor;

	// snake description

	int speed;
	int snake_length;
	std::list<Direction::Direction> snakeDirections;
	std::vector<sf::RectangleShape> body;
	Direction::Direction lastDir;

	int score = 0;

	float secondsSinceLastMove = 0;

	bool needToUpdateLength = false;
	bool local = true;

	int playerIndex;
	std::array<sf::Keyboard::Key, 4> currentScheme;

	std::array<std::array<sf::Keyboard::Key, 4>, 2> controlSchemes = {{
		{ sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down },
		{ sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S }
	}};
};
