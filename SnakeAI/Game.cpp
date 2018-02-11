#include "Game.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>

// initialization

bool Game::init() {
	// init game

	sf::Clock renderClock;
	sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	_window.create(videoMode, "Snake");
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(FRAMES_PER_SECOND);

	if (!font.loadFromFile("arial.ttf")) return false;

	setup();

	return true;
}

void Game::setup() {
	splashText.setFont(font);
	splashText.setString("Snake AI");
	splashText.setFillColor(sf::Color::Blue);
	splashText.setPosition(sf::Vector2f(0, 0));
	splashText.setCharacterSize(100);
	splashText.setPosition((SCREEN_WIDTH / 2) - (splashText.getGlobalBounds().width / 2), 200);


}

void Game::start() {
	// game start and loop

	_gameState = ShowingSplash;

	std::cout << "splash" << std::endl;

	while (_gameState == ShowingSplash) {
		splashLoop();
	}

	std::cout << "gameloop" << std::endl;

	while (!isExiting() && _window.isOpen()) {
		gameLoop();
	}

	_window.close();
}

// exiting

bool Game::isExiting() {
	return _gameState == Exiting;
}

void Game::exit() {
	_gameState = Exiting;
}

// splash loop

void Game::splashLoop() {
	sf::Event currEvent;

	while (_window.pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			exit();
		}
	}

	_window.clear(sf::Color::Black);

	if (!(splashText.getFillColor().a > 1)) {
		_gameState = Playing;
		return;
	}

	splashText.setFillColor(sf::Color(255, 255, 255, splashText.getFillColor().a - 2.5));

	_window.draw(splashText);

	_window.display();
}

// main game loop

void Game::gameLoop() {

	processEvents();

	_window.clear(sf::Color::Black);

	display();

	_window.display();
	
	renderClock.restart();
}

void display() {
	snake.display();
}

void Game::processEvents() {
	sf::Event currEvent;

	while (_window.pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			exit();
		}
	}
}