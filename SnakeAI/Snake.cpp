#include "Snake.h"



Snake::Snake(sf::RenderWindow *wind)
{
	screen = wind;

	bodyColor = sf::Color::Green;
	headColor = sf::Color::Blue;

	snake_length = 1;

}


Snake::~Snake()
{
}
