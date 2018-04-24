#include "Renderable.h"

Renderable::Renderable(sf::RenderWindow *sf) {

}

Renderable::~Renderable()
{
}

// meant to be overriden
void Renderable::display()
{
}

void Renderable::update(float dt) {
}

// size and location
sf::Vector2f Renderable::getSize() {
	return sf::Vector2f(this->width, this->height);
}

sf::Vector2f Renderable::getLocation() {
	return sf::Vector2f(this->x, this->y);
}

