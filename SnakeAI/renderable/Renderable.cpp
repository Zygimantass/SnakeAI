#include "Renderable.h"

Renderable::Renderable(sf::RenderWindow *sf) {

}

Renderable::~Renderable()
{
}

void Renderable::display()
{
}

void Renderable::update(float dt) {
}

sf::Vector2f Renderable::getSize() {
	return sf::Vector2f(this->width, this->height);
}

sf::Vector2f Renderable::getLocation() {
	return sf::Vector2f(this->x, this->y);
}

