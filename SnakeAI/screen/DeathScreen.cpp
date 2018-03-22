#include "DeathScreen.h"
#include <SFML/Graphics.hpp>
#include "../Game.h"
#include <string>

DeathScreen::~DeathScreen()
{
}

void DeathScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	scoreText.setFont(font);
	scoreText.setString("Score: ");
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(50);
	scoreText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2) - (scoreText.getGlobalBounds().width / 2), 200);
}

void DeathScreen::setScore(int score) {
	this->score = score;
	scoreText.setString("Score: " + std::to_string(score));
}

void DeathScreen::loop() {
	this->processEvents();

	sf->clear(sf::Color::Black);

	sf->draw(scoreText);

	sf->display();
}

void DeathScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}
	}
}
