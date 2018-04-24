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

// Snake renderable, inherits Renderable
class Snake: public Renderable
{
public:
	// Snake size
	static const int SIZE = 16;

	// ctor, takes window and player index
	Snake(sf::RenderWindow *sf, int playerIndex) : Renderable(sf) {
		this->sf = sf;

		// set color based on player number

		if (playerIndex == 0) {
			this->bodyColor = sf::Color::Green;
			this->headColor = sf::Color::Yellow;
		} else {
			this->bodyColor = sf::Color::Red;
			this->headColor = sf::Color::Blue;
		}

		// our length
		
		this->snake_length = 1;

		this->speed = 10;

		// setting a random position of our snake

		int maxX = (Constants::SCREEN_WIDTH - Snake::SIZE) / Snake::SIZE;
		int maxY = (Constants::SCREEN_HEIGHT - Snake::SIZE) / Snake::SIZE;
		int gridX = Utils::getRandomInt(0, maxX / 2);
		int gridY = Utils::getRandomInt(0, maxY / 2);

		this->x = gridX * Snake::SIZE;
		this->y = gridY * Snake::SIZE;
		
		this->width = Snake::SIZE;
		this->height = Snake::SIZE;

		// pushing the lastDirection, and populating the body with a head

		this->lastDir = Direction::Direction::DOWN;

		snakeDirections.push_back(Direction::Direction::DOWN);
		body.push_back(Utils::getRectangleAt(sf::Vector2f((float) this->x, (float) this->y), sf::Vector2f(16, 16), this->headColor));
		
		// setting a keyboard scheme

		this->playerIndex = playerIndex;
		this->currentScheme = this->controlSchemes[playerIndex];
	};

	~Snake();

	// debugging
	friend std::ostream& operator<<(std::ostream& os, const Snake& snake) {
		os << "[Snake] loc: (" << snake.x << ", " << snake.y << ")" << ", length: " << snake.snake_length;
		return os;
	}
	// prints the body for debugging
	std::ostringstream printBody();

	// body
	std::vector<sf::RectangleShape> getBody() {
		return this->body;
	}

	// getting snake's direction
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

	// score mgmt
	int getScore();
	void addScore();
	void addScore(int score);

protected:
	int ateFood();

	// snake color
	sf::Color headColor;
	sf::Color bodyColor;

	// snake description
	int speed;
	int snake_length;
	std::list<Direction::Direction> snakeDirections;
	std::vector<sf::RectangleShape> body;
	Direction::Direction lastDir;

	// score
	int score = 0;

	// move every x seconds
	float secondsSinceLastMove = 0;

	// bool for movement
	bool needToUpdateLength = false;
	bool local = true;

	// keyboard schemes for different player indexes
	int playerIndex;
	std::array<sf::Keyboard::Key, 4> currentScheme;

	std::array<std::array<sf::Keyboard::Key, 4>, 2> controlSchemes = {{
		{ sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down },
		{ sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S }
	}};
};
