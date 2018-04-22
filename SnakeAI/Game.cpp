#include "Game.h"

#include "ui/Callback.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

#include "renderable/Renderable.h"
#include "renderable/Snake.h"
#include "renderable/Food.h"
#include "util/Logging.h"

Game* Game::m_pInstance = NULL;

// singleton instance

Game* Game::getInstance() {
	if (!Game::m_pInstance)
		Game::m_pInstance = new Game;

	return Game::m_pInstance;
}

// initialization

bool Game::init() {
	// init game

	gen.seed(rd());

	sf::Clock renderClock;
	sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	_window.create(videoMode, "Snake");
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(FRAMES_PER_SECOND);

	if (!font.loadFromFile("./resources/arial.ttf")) return false;

	setup();

	return true;
}

void Game::setup() {
	this->splashScreen = new SplashScreen(&this->_window);
	this->menuScreen = new MenuScreen(&this->_window);
	this->pauseScreen = new PauseScreen(&this->_window);
	this->deathScreen = new DeathScreen(&this->_window);
	this->twoPlayerDeathScreen = new TwoPlayerDeathScreen(&this->_window);
	this->gameScreen = new GameScreen(&this->_window);
}

void Game::start() {
	// game start and loop

	switchGameState(ShowingSplash);

	logger::print("entering game loop");

	while (!isExiting() && _window.isOpen()) {
		if (_gameState == ShowingSplash)
			splashScreen->loop();
		if (_gameState == ShowingMenu)
			menuScreen->loop();
		if (_gameState == Playing)
			gameScreen->loop();
		if (_gameState == Paused)
			pauseScreen->loop();
		if (_gameState == GameOver)
			deathScreen->loop();
		if (_gameState == TwoPlayerGameOver)
			twoPlayerDeathScreen->loop();
	}

	_window.close();
}

void Game::reset() {
	delete this->snake;
	this->snake = new Snake(&_window, 0);
	
	if (this->playerCount > 1) {
		this->secondSnake = new Snake(&_window, 1);
	}
	
	std::ostringstream aaa = snake->printBody();
	std::cout << aaa.str() << std::endl;

	foods.clear();

	addFood(this->playerCount);
}

// exiting

bool Game::isExiting() {
	return _gameState == Exiting;
}

void Game::exit() {
	for (auto& r : foods)
		delete r;

	_gameState = Exiting;
}

// snake

Snake* Game::getSnake() {
	return this->snake;
}

Snake* Game::getSecondSnake() {
	return this->secondSnake;
}

// game state mgmt

void Game::switchGameState(GameState state) {
	switch (state) {
	case ShowingSplash:
		break;
	case GameOver:
		deathScreen->setScore(snake->getScore());
		break;
	case TwoPlayerGameOver:
		int victoriousPlayer = -1;

		if (snake->died() && secondSnake->died()) {
			victoriousPlayer = 0;
		}
		else if (!snake->died() && secondSnake->died()) {
			victoriousPlayer = 1;
		}
		else if (snake->died() && !secondSnake->died()) {
			victoriousPlayer = 2;
		}

		twoPlayerDeathScreen->setScore(snake->getScore(), secondSnake->getScore(), victoriousPlayer);
		break;
	}

	_gameState = state;
}

// misc. functions

int Game::getRandomInt(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}

sf::Font Game::getFont() {
	return this->font;
}

// food mgmt

void Game::addFood(int cnt) {
	for (int i = 0; i < cnt; i++) {

		bool foodPosGood = false;

		sf::Vector2f foodLoc;

		while (!foodPosGood) {
			int maxX = (Game::getInstance()->SCREEN_WIDTH - Food::SIZE) / Food::SIZE;
			int maxY = (Game::getInstance()->SCREEN_HEIGHT - Food::SIZE) / Food::SIZE;

			int x = Utils::getRandomInt(0, maxX);
			int y = Utils::getRandomInt(0, maxY);
			
			foodLoc = sf::Vector2f((float) x * 16, (float) y * 16);

			if (this->playerCount == 1) {
				foodPosGood = !snake->collides(foodLoc);
			}
			else if (this->playerCount == 2) {
				foodPosGood = !snake->collides(foodLoc) && !secondSnake->collides(foodLoc);
			}
			else {
				foodPosGood = false;
			}
		}
		
		foods.push_back(new Food(&_window, (int) foodLoc.x, (int) foodLoc.y));
	}
}