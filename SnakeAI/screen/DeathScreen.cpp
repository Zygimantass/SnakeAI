#include "DeathScreen.h"
#include <SFML/Graphics.hpp>
#include "../Game.h"
#include <string>
#include "../util/Logging.h"

DeathScreen::~DeathScreen()
{
}

// setups the deathscreen
void DeathScreen::setup() {
	// loading font
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	// loading score text
	scoreText.setFont(font);
	scoreText.setString(L"Taškai: ");
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(50);

	// loading reset button
	resetButton = UIButton(this->screen, (Game::getInstance()->SCREEN_WIDTH / 2) - 150, 400, 300, 100, L"Žaisti dar kartą", 30, "./resources/arial.ttf");
	resetButton.bind(std::bind(&DeathScreen::reset, this));
}

// score mgmt
void DeathScreen::setScore(int score) {
	this->score = score;
	scoreText.setString(L"Taškai: " + std::to_wstring(score));

	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin((textRect.left + textRect.width) / 2.0f, 0);
	scoreText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2.0f), 200);
}

// main deathscreen loop
void DeathScreen::loop() {
	// processing event
	this->processEvents();

	// drawing screen and button
	screen->clear(sf::Color::Black);

	screen->draw(scoreText);
	resetButton.display();

	screen->display();
}

void DeathScreen::processEvents() {
	sf::Event currEvent;

	while (screen->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			// check for exit
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			// check for resetbutton click
			resetButton.click(currEvent);
		}
	}
}

// resetting and setting the game state to menu
void DeathScreen::reset() {
	Game::getInstance()->reset();
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::Main);
	Game::getInstance()->switchGameState(Game::ShowingMenu);
}
