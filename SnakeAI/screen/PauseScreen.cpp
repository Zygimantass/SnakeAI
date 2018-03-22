#include "PauseScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

PauseScreen::~PauseScreen()
{
}

void PauseScreen::setup() {
}

void PauseScreen::loop() {
	this->processEvents();
}

void PauseScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::KeyReleased && currEvent.key.code == sf::Keyboard::P) {
			Game::getInstance()->switchGameState(Game::GameState::Playing);
		}
	}
}
