#pragma once
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <list>
#include <array>
#include "../util/Constants.h"
#include "../util/Utils.h"
#include "../util/Logging.h"
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
		//this->x = 0;
		//this->y = 0;
		
		this->width = Snake::SIZE;
		this->height = Snake::SIZE;

		this->lastDir = sf::Vector2<int>(0, 1);

		snakeDirections.push_back(sf::Vector2<int>(0, 1));
		body.push_back(Utils::getRectangleAt(sf::Vector2f((float) this->x, (float) this->y), sf::Vector2f(16, 16), this->headColor));
		
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

	// display, update
	void display() override;
	void update(float dt) override;
	
	// movement
	void switchDirection(sf::Vector2<int> dir);
	
	// death check
	bool died();

	// collision
	bool collidesHead(sf::Vector2f pos);
	bool collidesBody(sf::Vector2f pos);
	bool collides(sf::Vector2f pos);

	int getScore();
	void addScore();
	void addScore(int score);

private:
	void move(sf::Vector2<int> direction);
	int ateFood();
	sf::Color headColor;
	sf::Color bodyColor;

	// snake description

	int speed;
	int snake_length;
	std::list<sf::Vector2<int>> snakeDirections;
	std::vector<sf::RectangleShape> body;
	sf::Vector2<int> lastDir;

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
