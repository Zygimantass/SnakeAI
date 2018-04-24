#include "GameScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

GameScreen::~GameScreen()
{
}

// setting up screen
void GameScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	scoreOneText.setString(L"1 taškai: ");
	scoreOneText.setFont(font);
	scoreOneText.setFillColor(sf::Color::White);
	scoreOneText.setCharacterSize(20);

	scoreTwoText.setString(L"2 taškai: ");
	scoreTwoText.setFont(font);
	scoreTwoText.setFillColor(sf::Color::White);
	scoreTwoText.setCharacterSize(20);
}

// main loop
void GameScreen::loop() {
	// clock since last frame
	sf::Time elapsedTime = renderClock.restart();
	float dt = elapsedTime.asSeconds();
	
	// processing events (exit and P)
	this->processEvents();

	// clearing the screen
	sf->clear(sf::Color::Black);
	
	// displaying and updating the screen
	display();
	update(dt);

	// checking for snake death
	if (Game::getInstance()->getPlayerCount() == 2) {
		if (Game::getInstance()->getSecondSnake()->died() || Game::getInstance()->getSnake()->died()) Game::getInstance()->switchGameState(Game::GameState::TwoPlayerGameOver);
	}
	else {
		if (Game::getInstance()->getSnake()->died()) Game::getInstance()->switchGameState(Game::GameState::GameOver);
	}

	// displaying everything
	sf->display();
}

// HUD for score
void GameScreen::displayScore() {
	scoreOneText.setPosition(7, 7);
	scoreOneText.setString(L"1 taškai: " + std::to_wstring(Game::getInstance()->getSnake()->getScore()));

	sf->draw(scoreOneText);

	if (Game::getInstance()->getPlayerCount() == 2) {
		sf::FloatRect textTwoRect = scoreTwoText.getLocalBounds();
		scoreTwoText.setPosition(Constants::SCREEN_WIDTH - textTwoRect.width - 7, 7);

		scoreTwoText.setString(L"2 taškai: " + std::to_wstring(Game::getInstance()->getSecondSnake()->getScore()));
		
		sf->draw(scoreTwoText);
	}
}

// processing events
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

// displaying everything
void GameScreen::display() {
	// displaying snake
	Game::getInstance()->getSnake()->display();
	
	// displaying HUD
	displayScore();

	// displaying 2nd snake
	if (Game::getInstance()->getPlayerCount() == 2) Game::getInstance()->getSecondSnake()->display();

	// displaying food
	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->display();
	}
}

void GameScreen::update(float dt) {
	// updating snake
	Game::getInstance()->getSnake()->update(dt);
	
	// updating 2nd snake
	if (Game::getInstance()->getPlayerCount() == 2) Game::getInstance()->getSecondSnake()->update(dt);

	// updating food
	for (auto it = Game::getInstance()->foods.begin(); it != Game::getInstance()->foods.end(); it++) {
		Renderable* r = *it;
		r->update(dt);
	}
}