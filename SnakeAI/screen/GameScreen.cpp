#include "GameScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

GameScreen::~GameScreen()
{
}

void GameScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	scoreOneText.setString("P1 score: ");
	scoreOneText.setFont(font);
	scoreOneText.setFillColor(sf::Color::White);
	scoreOneText.setCharacterSize(20);

	scoreTwoText.setString("P2 score: ");
	scoreTwoText.setFont(font);
	scoreTwoText.setFillColor(sf::Color::White);
	scoreTwoText.setCharacterSize(20);
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

void GameScreen::displayScore() {
	scoreOneText.setPosition(7, 7);
	scoreOneText.setString("P1 score: " + std::to_string(Game::getInstance()->getSnake()->getScore()));

	sf->draw(scoreOneText);

	if (Game::getInstance()->getPlayerCount() == 2) {
		sf::FloatRect textTwoRect = scoreTwoText.getLocalBounds();
		scoreTwoText.setPosition(Constants::SCREEN_WIDTH - textTwoRect.width - 7, 7);

		scoreTwoText.setString("P2 score: " + std::to_string(Game::getInstance()->getSecondSnake()->getScore()));
		
		sf->draw(scoreTwoText);
	}
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
	displayScore();
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