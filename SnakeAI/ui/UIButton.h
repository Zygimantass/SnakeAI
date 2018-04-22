#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "Callback.h"
#include "../util/Logging.h"
#include <memory>

class UIButton
{
public:

	UIButton() {
	}
	
	UIButton(sf::RenderWindow *sf, int x, int y, int w, int h, std::string text, int size, std::string font) {
		this->sf = sf;
		this->fontName = font;
		this->font = std::make_shared<sf::Font>();

		this->pos.x = (float) x;
		this->pos.y = (float) y;

		this->size.x = (float) w;
		this->size.y = (float) h;

		buttonText.setString(text);
		buttonText.setCharacterSize(size);


		if (!(this->font)->loadFromFile(fontName)) {
			return;
		}

		buttonText.setFont(*this->font);

		this->setup();
	}
	~UIButton() {
	};

	bool inBounds(sf::Vector2f pos) {
		return buttonRect.getGlobalBounds().contains(pos);
	};

	bool inBounds(int x, int y) {
		sf::Vector2f pos((float) x, (float) y);
		return inBounds(pos);
	};

	void setup() {
		buttonRect.setPosition(this->pos);
		buttonRect.setFillColor(sf::Color::White);
		buttonRect.setSize(this->size);

		buttonText.setFillColor(sf::Color::Black);

		sf::FloatRect textRect = buttonText.getLocalBounds();

		buttonText.setOrigin((textRect.left + textRect.width) / 2.0f, (textRect.top + textRect.height) / 2.0f);
		buttonText.setPosition(this->pos.x + (this->size.x / 2), this->pos.y + (this->size.y / 2));
		
		logger::printCoords(sf::Vector2f(this->pos.x + (this->size.x / 2), this->pos.y + (this->size.y / 2)));

		this->initialized = true;
	};

	void click(sf::Event currEvent) {
		if (currEvent.type == sf::Event::MouseButtonReleased) {
			if (currEvent.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f clickLoc((float) currEvent.mouseButton.x, (float) currEvent.mouseButton.y);

				logger::print("clicked at: ");
				logger::printCoords(clickLoc);

				if (this->buttonRect.getGlobalBounds().contains(clickLoc)) {
					action();
				}
			}
		}
	}

	void display() {
		if (!initialized) return;

		sf->draw(buttonRect);
		sf->draw(buttonText);
	};
	
	void bind(std::function<void(void)> action) {
		this->action = action;
	}

private:
	sf::RenderWindow* sf;

	bool initialized = true;

	// size and position

	sf::Vector2f pos;
	sf::Vector2f size;

	// callback

	std::function<void(void)> action;

	// shape

	sf::RectangleShape buttonRect;

	// texts

	std::string fontName;
	sf::Text buttonText;
	std::shared_ptr<sf::Font> font;
};

