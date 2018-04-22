#include "GameScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

GameScreen::~GameScreen()
{
}

void GameScreen::setup() {
}

void GameScreen::loop() {
	sf::Time elapsedTime = renderClock.restart();
	float dt = elapsedTime.asSeconds();
	
	this->processEvents();

	processEvents();

	sf->clear(sf::Color::Black);

	update(dt);
	display();

	if (Game::getInstance()->getPlayerCount() == 2) {
		if (Game::getInstance()->getSecondSnake()->died() || Game::getInstance()->getSnake()->died()) Game::getInstance()->switchGameState(Game::GameState::TwoPlayerGameOver);
	}
	else {
		if (Game::getInstance()->getSnake()->died()) Game::getInstance()->switchGameState(Game::GameState::GameOver);
	}

	sf->display();
}

void GameScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::KeyReleased && currEvent.key.code == sf::Keyboard::P) {
			Game::getInstance()->switchGameState(Game::GameState::Paused);
		}
	}
}

void GameScreen::display() {
	Game::getInstance()->getSnake()->display();
	if (Game::getInstance()->getPlayerCount() == 2) Game::getInstance()->getSecondSnake()->display();

	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->display();
	}
}

void GameScreen::update(float dt) {
	Game::getInstance()->getSnake()->update(dt);
	
	if (Game::getInstance()->getPlayerCount() == 2) Game::getInstance()->getSecondSnake()->update(dt);

	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->update(dt);
	}
}