#include <SFML/Graphics.hpp>

namespace Utils {
	sf::RectangleShape getRectangleAt(sf::Vector2f loc, sf::Vector2f size, sf::Color color) {
		sf::RectangleShape rect;
		rect.setSize(size);
		rect.setPosition(loc);
		rect.setFillColor(color);
		return rect;
	}
}