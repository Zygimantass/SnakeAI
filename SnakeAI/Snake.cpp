#include "Snake.h"
#include "Renderable.h"
#include "Game.h"
#include "Logging.h"
#include <SFML/Graphics.hpp>

Snake::~Snake()
{

}

void Snake::display() {
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(Snake::SIZE, Snake::SIZE));
	shape.setFillColor(this->headColor);
	shape.setPosition(this->x, this->y);
	
	this->sf->draw(shape);
}

void Snake::update()
{

	if (this->lastMoveFrame == ((5 / speed) * 10)) {
		this->x += this->lastDir.x * 16;
		this->y -= this->lastDir.y * 16;
		lastMoveFrame = 0;
	}
	else {
		lastMoveFrame++;
	}

	if (this->x + 16 > Game::SCREEN_WIDTH) {
		this->x = 0;
	}

	if (this->x < 0) {
		this->x = Game::SCREEN_WIDTH - 16;
	}

	if (this->y + 16 > Game::SCREEN_HEIGHT) {
		this->y = 0;
	}

	if (this->y < 0) {
		this->y = Game::SCREEN_HEIGHT - 16;
	}
}

void Snake::switchDirection(sf::Vector2<int> dir) {
	this->lastDir = dir;
}
