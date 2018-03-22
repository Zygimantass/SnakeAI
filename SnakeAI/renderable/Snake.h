#pragma once
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <list>
#include "../util/Utils.h"
#include <sstream>

class Snake: public Renderable
{
public:
	static const int SIZE = 16;

	Snake(sf::RenderWindow *sf) : Renderable(sf) {
		this->sf = sf;

		this->bodyColor = sf::Color::Green;
		this->headColor = sf::Color::Yellow;

		this->snake_length = 1;

		this->speed = 6;
		
		this->x = 0;
		this->y = 0;
		this->width = Snake::SIZE;
		this->height = Snake::SIZE;

		this->lastDir = sf::Vector2<int>(0, 1);

		snakeDirections.push_back(sf::Vector2<int>(0, 1));
		body.push_back(Utils::getRectangleAt(sf::Vector2f(0, 0), sf::Vector2f(16, 16), this->headColor));
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
};