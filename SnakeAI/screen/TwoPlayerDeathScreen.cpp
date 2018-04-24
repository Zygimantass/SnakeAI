#include "TwoPlayerDeathScreen.h"
#include "../Game.h"
#include "../util/Constants.h"

// setting up screen
void TwoPlayerDeathScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	scoreOneText.setFont(font);
	scoreOneText.setString(L"Pirmo žaidėjo taškai: ");
	scoreOneText.setFillColor(sf::Color::White);
	scoreOneText.setCharacterSize(40);

	scoreTwoText.setFont(font);
	scoreTwoText.setString(L"Antro žaidėjo taškai: ");
	scoreTwoText.setFillColor(sf::Color::White);
	scoreTwoText.setCharacterSize(40);

	victoryText.setFont(font);
	victoryText.setString("Lygiosios!");
	victoryText.setFillColor(sf::Color::White);
	victoryText.setCharacterSize(55);

	resetButton = UIButton(this->screen, (Game::getInstance()->SCREEN_WIDTH / 2) - 150, 400, 300, 100, L"Žaisti iš naujo", 30, "./resources/arial.ttf");
	resetButton.bind(std::bind(&TwoPlayerDeathScreen::reset, this));
}

// setting the scores
void TwoPlayerDeathScreen::setScore(int scoreOne, int scoreTwo, int victoriousPlayerIndex) {
	this->scoreOne = scoreOne;
	this->scoreTwo = scoreTwo;
	this->victoriousPlayerIndex = victoriousPlayerIndex;

	// setting up scores and centering texts

	scoreOneText.setString(L"Pirmo žaidėjo taškai: " + std::to_wstring(scoreOne));
	scoreTwoText.setString(L"Antro žaidėjo taškai: " + std::to_wstring(scoreTwo));

	sf::FloatRect textOneRect = scoreOneText.getLocalBounds();
	scoreOneText.setOrigin((textOneRect.left + textOneRect.width) / 2.0f, 0);
	scoreOneText.setPosition((Constants::SCREEN_WIDTH / 2), 200);

	sf::FloatRect textTwoRect = scoreTwoText.getLocalBounds();
	scoreTwoText.setOrigin((textTwoRect.left + textTwoRect.width) / 2.0f, 0);
	scoreTwoText.setPosition((Constants::SCREEN_WIDTH / 2), 250);

	// setting the victorious people text and centering it

	if (this->victoriousPlayerIndex == 0) {
		victoryText.setString(L"Lygiosios!");
	}
	else if (this->victoriousPlayerIndex == 1) {
		victoryText.setString(L"Laimėjo pirmasis žaidėjas!");
	}
	else if (this->victoriousPlayerIndex == 2) {
		victoryText.setString(L"Laimėjo antrasis žaidėjas!");
	}

	sf::FloatRect victoryTextRect = victoryText.getLocalBounds();
	victoryText.setOrigin((victoryTextRect.left + victoryTextRect.width) / 2.0f, 0);
	victoryText.setPosition((Constants::SCREEN_WIDTH / 2), 100);
}

// main loop
void TwoPlayerDeathScreen::loop() {
	this->processEvents();

	screen->clear(sf::Color::Black);

	screen->draw(victoryText);
	screen->draw(scoreOneText);
	screen->draw(scoreTwoText);
	resetButton.display();

	screen->display();
}

// event processing
void TwoPlayerDeathScreen::processEvents() {
	sf::Event currEvent;

	while (screen->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			resetButton.click(currEvent);
		}
	}
}

// resetting game
void TwoPlayerDeathScreen::reset() {
	Game::getInstance()->reset();
	Game::getInstance()->menuScreen->switchMenuState(MenuScreen::Main);
	Game::getInstance()->switchGameState(Game::ShowingMenu);
}