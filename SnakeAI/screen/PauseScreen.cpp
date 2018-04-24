#include "PauseScreen.h"
#include "../Game.h"
#include "../util/Logging.h"

PauseScreen::~PauseScreen()
{
}

void PauseScreen::setup() {
	if (!font.loadFromFile("resources/arial.ttf")) {
		logger::print("failed");
		return;
	}

	pauseText.setFont(font);
	pauseText.setCharacterSize(100);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString(L"Pauzė");
	pauseText.setPosition((Game::getInstance()->SCREEN_WIDTH / 2) - (pauseText.getGlobalBounds().width / 2), 100);

	resetButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 150, 400, 300, 100, L"Žaisti dar kartą", 30, "./resources/arial.ttf");
	resetButton.bind(std::bind(&PauseScreen::reset, this));
}

void PauseScreen::loop() {
	this->processEvents();
	sf->clear(sf::Color::Black);
	
	sf->draw(pauseText);
	resetButton.display();
	
	sf->display();
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

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			resetButton.click(currEvent);
		}
	}
}

void PauseScreen::reset() {
	Game::getInstance()->reset();
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::Main);
	Game::getInstance()->switchGameState(Game::ShowingMenu);
}