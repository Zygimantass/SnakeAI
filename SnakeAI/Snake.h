#pragma once
#include "SFML/Graphics.hpp"
#include <list>

class Snake
{
public:
	Snake(sf::RenderWindow *);
	~Snake();

	void update();
	void display();
	void switchDirection(sf::Vector2<int> dir);
	bool died();
private:
	sf::RenderWindow *screen;

	sf::Color headColor;
	sf::Color bodyColor;

	// snake description

	int snake_length;
	std::list<sf::Vector2<int>> snakeDirections;
	sf::Vector2<int> lastDir;
	std::vector<sf::RectangleShape> body;
};

