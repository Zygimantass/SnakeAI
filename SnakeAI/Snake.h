#pragma once
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <list>

class Snake: public Renderable
{
public:
	static const int SIZE = 16;

	Snake(sf::RenderWindow *sf) : Renderable(sf) {
		this->sf = sf;

		this->bodyColor = sf::Color::Green;
		this->headColor = sf::Color::Blue;

		this->snake_length = 1;

		this->speed = 10;
		
		this->x = 0;
		this->y = 0;
		this->width = Snake::SIZE;
		this->height = Snake::SIZE;

		this->lastDir = sf::Vector2<int>(1, 0);
	};

	~Snake();

	void display() override;
	void update() override;
	void switchDirection(sf::Vector2<int> dir);
	bool died();
private:
	sf::RenderWindow *screen;

	sf::Color headColor;
	sf::Color bodyColor;

	// snake description

	int speed;
	int snake_length;
	std::list<sf::Vector2<int>> snakeDirections;
	sf::Vector2<int> lastDir;
	std::vector<sf::RectangleShape> body;

	int lastMoveFrame = 0;
};

