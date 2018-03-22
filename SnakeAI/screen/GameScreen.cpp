#include "GameScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

GameScreen::~GameScreen()
{
}

void GameScreen::setup() {
}

void GameScreen::loop() {
	sf::Time elapsedTime = Game::getInstance()->getRenderClock().restart();
	float dt = elapsedTime.asSeconds();
	
	this->processEvents();

	processEvents();

	sf->clear(sf::Color::Black);

	display();
	update(dt);

	sf->display();

	if (Game::getInstance()->getSnake()->died()) {
		Game::getInstance()->switchGameState(Game::GameState::GameOver);
	}
}

void GameScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::KeyReleased && currEvent.key.code == sf::Keyboard::P) {
			logger::print("entering pause");
			Game::getInstance()->switchGameState(Game::GameState::Paused);
		}
	}
}

void GameScreen::display() {
	Game::getInstance()->getSnake()->display();

	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->display();
	}
}

void GameScreen::update(float dt) {
	Game::getInstance()->getSnake()->update(dt);

	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->update(dt);
	}
}