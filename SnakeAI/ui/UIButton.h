#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "../util/Logging.h"
#include <memory>

// class for Button
class UIButton
{
public:
	// ctor
	UIButton() {
	}
	
	//ctor takes window, position, size, text, fontSize, font
	UIButton(sf::RenderWindow *sf, int x, int y, int w, int h, std::wstring text, int size, std::string font) {
		this->sf = sf;
		this->fontName = font;

		//shared pointer for font, because of weird bug
		this->font = std::make_shared<sf::Font>();

		this->pos.x = (float) x;
		this->pos.y = (float) y;

		this->size.x = (float) w;
		this->size.y = (float) h;

		buttonText.setString(text);
		buttonText.setCharacterSize(size);

		// loading font
		if (!(this->font)->loadFromFile(fontName)) {
			logger::print("load failed");
			return;
		}

		buttonText.setFont(*this->font);

		this->setup();
	}
	~UIButton() {
	};

	// checking for mouse in button
	bool inBounds(sf::Vector2f pos) {
		return buttonRect.getGlobalBounds().contains(pos);
	};

	bool inBounds(int x, int y) {
		sf::Vector2f pos((float) x, (float) y);
		return inBounds(pos);
	};

	// setup of button
	void setup() {
		buttonRect.setPosition(this->pos);
		buttonRect.setFillColor(sf::Color::White);
		buttonRect.setSize(this->size);

		buttonText.setFillColor(sf::Color::Black);

		sf::FloatRect textRect = buttonText.getLocalBounds();

		buttonText.setOrigin((textRect.left + textRect.width) / 2.0f, (textRect.top + textRect.height) / 2.0f);
		buttonText.setPosition(this->pos.x + (this->size.x / 2), this->pos.y + (this->size.y / 2));
		
		this->initialized = true;
	};

	// checking for button click
	void click(sf::Event currEvent) {
		if (currEvent.type == sf::Event::MouseButtonReleased) {
			if (currEvent.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f clickLoc((float) currEvent.mouseButton.x, (float) currEvent.mouseButton.y);

				if (this->buttonRect.getGlobalBounds().contains(clickLoc)) {
					// calling back

					action();
				}
			}
		}
	}

	// displaying button
	void display() {
		if (!initialized) return;

		sf->draw(buttonRect);
		sf->draw(buttonText);
	};

	// binding callback
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

