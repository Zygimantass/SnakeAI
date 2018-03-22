#include "SplashScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

SplashScreen::~SplashScreen()
{
}

void SplashScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	splashText.setFont(font);
	splashText.setString("Snake AI");
	splashText.setFillColor(sf::Color::Blue);
	splashText.setCharacterSize(100);
	splashText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2) - (splashText.getGlobalBounds().width / 2), 200);
}

void SplashScreen::loop() {
	this->processEvents();

	sf->clear(sf::Color::Black);

	if (!((int) splashText.getFillColor().a > 1)) {
		Game::getInstance()->switchGameState(Game::Playing);
		return;
	}

	splashText.setFillColor(sf::Color(255, 255, 255, splashText.getFillColor().a - 3));

	sf->draw(splashText);

	sf->display();
}

void SplashScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}
	}
}
