#pragma once
#include <SFML/Graphics.hpp>
namespace Utils {
	sf::RectangleShape getRectangleAt(sf::Vector2f loc, sf::Vector2f size, sf::Color color);
	int getRandomInt(int min, int max);
}