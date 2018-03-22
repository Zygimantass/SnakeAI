#pragma once
#include "Renderable.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "../util/Logging.h"

class Food: public Renderable
{
public:
	static const int SIZE = 16;

	Food(sf::RenderWindow *sf, int x, int y): Renderable(sf) {
		this->sf = sf;
	
		this->foodColor = sf::Color::Magenta;
		this->x = x;
		this->y = y;

		this->width = this->SIZE;
		this->height = this->SIZE;
	}

	~Food();

	void display() override;
	void eat();
private:
	sf::Color foodColor;

	bool eaten = false;
};

