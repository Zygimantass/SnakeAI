﻿#include "AboutScreen.h"
#include "../../util/Constants.h"
#include "../../Game.h"

// setting up about screen, putting in info
void AboutScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	aboutText.setFont(font);
	aboutText.setFillColor(sf::Color::White);
	aboutText.setString(L"Šio \u017eaidimo tikslas yra suvalgyti kuo\ndaugiau maisto (  ) ir nemirti. Mirti galima palietus\nsieną, savo kūną arba kito žaidėjo kūną.\nP - sustabdo žaidimą,\nWASD ir rodyklės kontroliuoja gyvatėles");

	sf::FloatRect textRect = aboutText.getLocalBounds();
	aboutText.setOrigin((textRect.left + textRect.width) / 2.0f, 0);
	aboutText.setPosition((Constants::SCREEN_WIDTH / 2), 200);

	// binding back button

	backButton = UIButton(this->screen, (Constants::SCREEN_WIDTH / 2) - 150, 400, 300, 50, L"Atgal", 20, "./resources/arial.ttf");
	backButton.bind(std::bind(&AboutScreen::back, this));
}

// main loop
void AboutScreen::loop() {
	processEvents();
	screen->clear(sf::Color::Black);

	sf::RectangleShape shape;

	shape.setSize(sf::Vector2f(16, 16));
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(407, 254);
	shape.setOutlineThickness(0);
	screen->draw(shape);

	screen->draw(aboutText);
	backButton.display();

	screen->display();
}

// processing events for mouse clicks or exits
void AboutScreen::processEvents() {
	sf::Event currEvent;

	while (screen->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			backButton.click(currEvent);
		}
	}
}

// back function
void AboutScreen::back() {
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::Main);
}