#include "MainScreen.h"
#include "../../Game.h"
#include "../../util/Logging.h"

void MainScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	titleText.setString("Snake");
	titleText.setCharacterSize(75);
	titleText.setFillColor(sf::Color::White);
	titleText.setFont(font);

	sf::FloatRect textRect = titleText.getLocalBounds();
	titleText.setOrigin((textRect.left + textRect.width) / 2.0f, 0);
	titleText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2), 150);
	
	this->playButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 100, 325, 200, 50, "Play", 20, "./resources/arial.ttf");
	this->playButton.bind(std::bind(&MainScreen::play, this));

	this->exitButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 100, 400, 200, 50, "Exit", 20, "./resources/arial.ttf");
	this->exitButton.bind(std::bind(&MainScreen::exit, this));
}

void MainScreen::loop() {
	this->processEvents();

	sf->clear(sf::Color::Black);
	this->exitButton.display();
	this->playButton.display();
	sf->draw(titleText);

	sf->display();
}

void MainScreen::exit() {
	Game::getInstance()->exit();
}

void MainScreen::play() {
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::PlayerCount);
}

void MainScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			exitButton.click(currEvent);
			playButton.click(currEvent);
		}
	}
}