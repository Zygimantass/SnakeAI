#include "MainScreen.h"
#include "../../Game.h"
#include "../../util/Logging.h"


// setting up main menu, binding functions to buttons, and creating buttons
void MainScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	titleText.setString("Snake");
	titleText.setCharacterSize(75);
	titleText.setFillColor(sf::Color::White);
	titleText.setFont(font);

	sf::FloatRect textRect = titleText.getLocalBounds();
	titleText.setOrigin((textRect.left + textRect.width) / 2.0f, 0);
	titleText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2.0f), 150);
	
	this->playButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 100, 325, 200, 50, L"Žaisti", 20, "./resources/arial.ttf");
	this->playButton.bind(std::bind(&MainScreen::play, this));

	this->aboutButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 100, 400, 200, 50, L"Apie", 20, "./resources/arial.ttf");
	this->aboutButton.bind(std::bind(&MainScreen::about, this));

	this->exitButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 100, 475, 200, 50, L"Išeiti", 20, "./resources/arial.ttf");
	this->exitButton.bind(std::bind(&MainScreen::exit, this));
}

// main loop
void MainScreen::loop() {
	this->processEvents();

	sf->clear(sf::Color::Black);
	this->exitButton.display();
	this->playButton.display();
	this->aboutButton.display();
	sf->draw(titleText);

	sf->display();
}

// exiting
void MainScreen::exit() {
	Game::getInstance()->exit();
}

// playing
void MainScreen::play() {
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::PlayerCount);
}

// switching to about menu
void MainScreen::about() {
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::About);
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
			aboutButton.click(currEvent);
		}
	}
}