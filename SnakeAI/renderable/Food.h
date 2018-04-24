#pragma once
#include "Renderable.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "../util/Logging.h"

// Food renderable, inherits Renderable
class Food: public Renderable
{
public:
	// Food size
	static const int SIZE = 16;

	// ctor, takes the window, and position (x, y)
	Food(sf::RenderWindow *sf, int x, int y): Renderable(sf) {
		this->sf = sf;
	
		this->foodColor = sf::Color::Magenta;
		this->x = x;
		this->y = y;

		this->width = this->SIZE;
		this->height = this->SIZE;
	}

	~Food();

	// displays the food
	void display() override;
private:
	sf::Color foodColor;
};

