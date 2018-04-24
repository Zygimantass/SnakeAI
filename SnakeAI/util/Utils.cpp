#include <SFML/Graphics.hpp>
#include "../Game.h"

namespace Utils {
	// getting a rectangleshape at loc, size of size and color of color
	sf::RectangleShape getRectangleAt(sf::Vector2f loc, sf::Vector2f size, sf::Color color) {
		sf::RectangleShape rect;
		rect.setSize(size);
		rect.setPosition(loc);
		rect.setFillColor(color);
		return rect;
	}

	// getting random integer
	int getRandomInt(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);

		return dist(Game::getInstance()->gen);
	}
}