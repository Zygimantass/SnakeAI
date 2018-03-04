#include "Game.h"
#include "Renderable.h"
#include "Snake.h"
#include "Logging.h"
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

	this->snake = new Snake(&_window);
}

void Game::start() {
	// game start and loop

	_gameState = ShowingSplash;

	logger::print("showing splash");

	while (_gameState == ShowingSplash) {
		splashLoop();
	}

	logger::print("entering game loop");

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
	for (auto& r : renderables)
		delete r;

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
	update();

	_window.display();
	
	renderClock.restart();
}

void Game::display() {
	this->snake->display();

	for (auto it = renderables.begin(); it != renderables.end(); it++) {
		Renderable* r = *it;
		r->display();
	}
}

void Game::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->snake->switchDirection(sf::Vector2<int>(-1, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->snake->switchDirection(sf::Vector2<int>(1, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->snake->switchDirection(sf::Vector2<int>(0, 1));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->snake->switchDirection(sf::Vector2<int>(0, -1));
	}

	this->snake->update();

	for (auto it = renderables.begin(); it != renderables.end(); it++) {
		Renderable* r = *it;
		r->update();
	}
}

void Game::processEvents() {
	sf::Event currEvent;

	while (_window.pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			exit();
		}
	}
}

