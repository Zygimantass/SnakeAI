#include "Food.h"

Food::~Food()
{
}

// displaying our food rect
void Food::display() {
	sf::RectangleShape shape;

	shape.setSize(sf::Vector2f(this->width, this->height));
	shape.setFillColor(this->foodColor);
	shape.setPosition(this->x, this->y);
	shape.setOutlineThickness(0);
	this->sf->draw(shape);
}